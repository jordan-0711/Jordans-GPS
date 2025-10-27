// -------------------------------------------------------------------------------------------------
// Shared tools & recipe helpers
// -------------------------------------------------------------------------------------------------

// -------------------- Tool classification (used by slip/wet logic etc.) --------------------
enum toolCategory
{
    TOOL_SMALL_BLADE,
    TOOL_LARGE_BLADE,
    TOOL_AXE,
    TOOL_SAW
};

string toolNoun(toolCategory cat)
{
    switch (cat)
    {
        case toolCategory.TOOL_SMALL_BLADE:
            return "knife blade";
        case toolCategory.TOOL_LARGE_BLADE:
            return "large blade";
        case toolCategory.TOOL_AXE:
            return "axe head";
        case toolCategory.TOOL_SAW:
            return "saw blade";
        default:
            return "blade";
    }
    return "blade";
}

toolCategory GetToolCategory(ItemBase tool)
{
    if (!tool) return toolCategory.TOOL_SMALL_BLADE;

    string toolName = tool.GetType();

    // Small blades
    if (toolName == "KitchenKnife")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "SteakKnife")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "CombatKnife")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "HuntingKnife")
        return toolCategory.TOOL_SMALL_BLADE;
    if (toolName == "Msp_VorpalKnife")
        return toolCategory.TOOL_SMALL_BLADE;
    // Large blades
    if (toolName == "Cleaver")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "KukriKnife")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "FangeKnife")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "AK_Bayonet")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "M9A1_Bayonet")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "Mosin_Bayonet")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "SNAFU_SKS_Bayonet")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "SNAFU_Kabar")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "SNAFU_Kabar_BK")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "Machete")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "CrudeMachete")
        return toolCategory.TOOL_LARGE_BLADE;
    if (toolName == "OrientalMachete")
        return toolCategory.TOOL_LARGE_BLADE;
    // Axes
    if (toolName == "Hatchet")
        return toolCategory.TOOL_AXE;
    if (toolName == "WoodAxe")
        return toolCategory.TOOL_AXE;
    if (toolName == "FirefighterAxe")
        return toolCategory.TOOL_AXE;
    // Saws
    if (toolName == "HandSaw")
        return toolCategory.TOOL_SAW;
    if (toolName == "Hacksaw")
        return toolCategory.TOOL_SAW;
    // Default
    return toolCategory.TOOL_SMALL_BLADE;
}

// -------------------- Generic recipe helpers --------------------
class jrdn_gps_utils
{
    // Randomly pick one of two classnames (50/50) and return the roll (0 or 1)
    static int RandomPickTwo(string a, string b, out string pick)
    {
        int r = Math.RandomInt(0, 2); // 0..1
        if (r == 0) pick = a;
        else        pick = b;
        return r;
    }

    // Read inheritance from one source item (health ratio 0..1, wetness 0..1)
    static void ReadInheritedState(ItemBase src, out float inheritRatio, out float inheritWet)
    {
        inheritRatio = -1.0;
        inheritWet   = -1.0;

        if (!src) return;

        float srcMax = src.GetMaxHealth("", "");
        if (srcMax > 0.0)
            inheritRatio = src.GetHealth("", "") / srcMax;

        inheritWet = src.GetWet();
    }

    // Apply a stored health ratio & wetness to an item
    static void ApplyHealthWet(ItemBase item, float inheritRatio, float inheritWet)
    {
        if (!item) return;

        if (inheritRatio >= 0.0)
        {
            float outMax = item.GetMaxHealth("", "");
            if (outMax > 0.0)
            {
                float outHP = outMax * inheritRatio;
                item.SetHealth("", "", outHP);
            }
        }

        if (inheritWet >= 0.0)
            item.SetWet(inheritWet);
    }

    // Keep placeholder (if pick matches) or spawn class at player's feet; always apply inheritance.
    // placeholderClassname: pass the class of the default AddResult (or "" if none).
    static void KeepOrSpawnResult(string pick, array<ItemBase> results, PlayerBase player, float inheritRatio, float inheritWet, string placeholderClassname)
    {
        ItemBase res0 = null;
        if (results && results.Count() > 0)
            res0 = results[0];

        // If the placeholder matches the desired class, keep and apply inheritance
        if (res0 && placeholderClassname != "" && pick == placeholderClassname)
        {
            ApplyHealthWet(res0, inheritRatio, inheritWet);
            return;
        }

        // Otherwise, remove the placeholder (if any) and spawn the chosen class
        if (res0)
            GetGame().ObjectDelete(res0);

        if (!player) return;

        vector pos = player.GetPosition();
        EntityAI spawned = GetGame().CreateObjectEx(pick, pos, ECE_PLACE_ON_SURFACE);
        ApplyHealthWet(ItemBase.Cast(spawned), inheritRatio, inheritWet);
    }

    // Spawn a class at player's feet and return it as ItemBase (or null)
    static ItemBase SpawnAtFeet(string classname, PlayerBase player)
    {
        if (!player) return null;
        vector pos = player.GetPosition();
        return ItemBase.Cast(GetGame().CreateObjectEx(classname, pos, ECE_PLACE_ON_SURFACE));
    }

    // Drop the item currently in hands (server-safe)
    static void DropItemInHands(PlayerBase player)
    {
        if (!player) return;
        EntityAI inHands = player.GetItemInHands();
        if (inHands && player.GetHumanInventory())
            player.GetHumanInventory().DropEntity(InventoryMode.SERVER, player, inHands);
    }

    // Dryness rule: true if BOTH items are below the given threshold (e.g., STATE_DAMP)
    static bool IsBothBelowWetThreshold(ItemBase a, ItemBase b, float threshold)
    {
        if (!a || !b) return false;
        if (a.GetWet() >= threshold) return false;
        if (b.GetWet() >= threshold) return false;
        return true;
    }

    // Power detection by type (slot-agnostic)
    static void DetectPower(ItemBase device, out bool has9V, out bool hasCar, out bool isBaseRadio)
    {
        has9V = false;
        hasCar = false;
        isBaseRadio = false;

        if (!device || !device.GetInventory()) return;

        isBaseRadio = device.IsKindOf("BaseRadio");

        int ac = device.GetInventory().AttachmentCount();
        for (int ai = 0; ai < ac; ai++)
        {
            EntityAI att = device.GetInventory().GetAttachmentFromIndex(ai);
            if (!att) continue;

            if (att.IsKindOf("Battery9V"))      has9V = true;
            else if (att.IsKindOf("CarBattery")) hasCar = true;
            // else if (att.IsKindOf("TruckBattery")) hasCar = true; // if you add it later
        }
    }

    // Shock only (no stamina). Drops item in hands and shows a message by wetness/battery type.
    static void ShockIfPowered(ItemBase source, PlayerBase player)
    {
        if (!source || !player || !source.GetInventory()) return;

        bool has9V;
        bool hasCar;
        bool isBaseRadio;
        DetectPower(source, has9V, hasCar, isBaseRadio);

        if (!(has9V || hasCar)) return;

        float wet = source.GetWet(); // 0..1

        float shockSeverity;
        if (hasCar) shockSeverity = 30.0;
        else        shockSeverity = 4.0;

        float shockMultiplier = 1.0;

        if (wet >= GameConstants.STATE_WET)
        {
            if (hasCar) shockSeverity = 40.0;
            else        shockSeverity = 5.0;

            if      (wet < GameConstants.STATE_SOAKING_WET) shockMultiplier = 1.5;
            else if (wet < GameConstants.STATE_DRENCHED)    shockMultiplier = 1.9;
            else                                            shockMultiplier = 2.5;

            if (isBaseRadio)
                shockSeverity = shockSeverity + 15.0;
        }

        float finalMag = shockSeverity * shockMultiplier;
        if (finalMag > 60.0) finalMag = 60.0;

        player.AddHealth("", "Shock", -finalMag);

        DropItemInHands(player);

        if (wet >= GameConstants.STATE_WET)
        {
            if (isBaseRadio) player.MessageImportant("A severe jolt from the powered, wet base radio zaps you!");
            else             player.MessageImportant("A strong jolt from the powered, wet device zaps you!");
        }
        else
        {
            player.MessageImportant("A small jolt from the powered device zaps you.");
        }
    }

    // Cut-wires utility: transfer wetness to results and evaluate slip chance
    static void ApplyWetTransferAndSlip(ItemBase source_item, ItemBase tool, array<ItemBase> results, PlayerBase player)
    {
        if (!source_item) return;

        float wet = source_item.GetWet();
        if (wet < GameConstants.STATE_WET) return;

        // Transfer wetness and apply small damage to crafted results (after inheritance)
        for (int i = 0; i < results.Count(); i++)
        {
            ItemBase res = results[i];
            if (!res) continue;

            res.SetWet(wet);
            res.AddHealth("", "", -10.0);
        }

        if (GetGame().IsServer() && player)
        {
            float slipChance;
            if      (wet < GameConstants.STATE_SOAKING_WET) slipChance = 0.15;
            else if (wet < GameConstants.STATE_DRENCHED)    slipChance = 0.35;
            else                                            slipChance = 0.60;

            toolCategory cat = GetToolCategory(tool);
            switch (cat)
            {
                case toolCategory.TOOL_LARGE_BLADE:
                    slipChance += 0.20;
                    break;
                case toolCategory.TOOL_AXE:
                    slipChance += 0.30;
                    break;
                case toolCategory.TOOL_SAW:
                    slipChance += 0.10;
                    break;
                default:
                    break;
            }

            if (slipChance < 0.0) slipChance = 0.0;
            if (slipChance > 0.95) slipChance = 0.95;

            if (Math.RandomFloat01() < slipChance)
            {
                string noun = toolNoun(cat);

                ItemBase gloves = ItemBase.Cast(player.FindAttachmentBySlotName("Gloves"));
                if (gloves)
                {
                    gloves.AddHealth("", "", -5.0);
                    player.MessageImportant("The " + noun + " slipped on the wet plastic surface, luckily your gloves took the hit.");
                }
                else
                {
                    string bodyPart;
                    if (Math.RandomInt(0, 2) == 0) bodyPart = "LeftForeArmRoll";
                    else                            bodyPart = "RightForeArmRoll";

                    if (player.m_BleedingManagerServer)
                    {
                        player.m_BleedingManagerServer.AttemptAddBleedingSourceBySelection(bodyPart);
                        player.MessageImportant("The " + noun + " slipped on the wet plastic surface, you should be wearing gloves.");
                    }
                }
            }
        }
    }
}
