//----------------------------------------------------------------------------------------------------------------------
// Debug options
const bool JRDN_GPS_DEBUG = true;
const bool JRDN_GPS_TEST_FORCE_SLIP    = false; // set true to guarantee slip
const bool JRDN_GPS_TEST_FORCE_NO_SLIP = false; // set true to guarantee NO slip
void JRDN_Log(string msg)
{
	if (GetGame() && GetGame().IsServer())
	{
		Print("[JRDN_GPS] " + msg);
	}
}
class salvageWires extends RecipeBase
{
	override void Init()
	{
		// -------------------------------------------------------------------------------------------------
		// Common
		// -------------------------------------------------------------------------------------------------
		m_Name = "Cut wires";
		m_IsInstaRecipe = false;					// should this recipe be performed instantly without animation
		m_AnimationLength = 2;						// animation length in relative time units
		m_Specialty = 0;							// relates to the soft skills stats for players - recommended not to change

		// -------------------------------------------------------------------------------------------------
		// Conditions
		// -------------------------------------------------------------------------------------------------
		m_MinDamageIngredient[0]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[0] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[0]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[0] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[0]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[0]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.
		m_MinDamageIngredient[1]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[1] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[1]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[1] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[1]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[1]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.

		// -------------------------------------------------------------------------------------------------
		// Ingredient 1
		// -------------------------------------------------------------------------------------------------
		// PreferredTools
		InsertIngredient(0, "SteakKnife");
		InsertIngredient(0, "KitchenKnife");
		InsertIngredient(0, "CombatKnife");
		InsertIngredient(0, "HuntingKnife");
		InsertIngredient(0, "Cleaver");
		InsertIngredient(0, "AK_Bayonet");
		InsertIngredient(0, "M9A1_Bayonet");
		InsertIngredient(0, "SNAFU_Kabar");
		InsertIngredient(0, "Msp_VorpalKnife");
		InsertIngredient(0, "KukriKnife");
		InsertIngredient(0, "FangeKnife");
		InsertIngredient(0, "Mosin_Bayonet");
		InsertIngredient(0, "SNAFU_SKS_Bayonet");
		InsertIngredient(0, "Machete");
		InsertIngredient(0, "CrudeMachete");
		InsertIngredient(0, "OrientalMachete");
		// NotPreferredTools
		InsertIngredient(0, "Hatchet");
		InsertIngredient(0, "WoodAxe");
		InsertIngredient(0, "FirefighterAxe");
		InsertIngredient(0, "FirefighterAxe_Black");
		InsertIngredient(0, "FirefighterAxe_Green");
		InsertIngredient(0, "Pickaxe");
		InsertIngredient(0, "Iceaxe");
		InsertIngredient(0, "HandSaw");
		InsertIngredient(0, "Hacksaw");
		InsertIngredient(0, "Sword");

		m_IngredientAddHealth[0] = -10;// 0 = do nothing
        m_IngredientSetHealth[0] = -1; // -1 = do nothing
        m_IngredientAddQuantity[0] = 0;// 0 = do nothing
        m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
        m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient


		// -------------------------------------------------------------------------------------------------
		// Ingredient 2
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(1,"Spotlight");
		InsertIngredient(1,"CableReel");
		m_IngredientAddHealth[1] = 0;// 0 = do nothing
        m_IngredientSetHealth[1] = -1; // -1 = do nothing
        m_IngredientAddQuantity[1] = -1;// 0 = do nothing
        m_IngredientDestroy[1] = true;//true = destroy, false = do nothing
        m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this 


		// -------------------------------------------------------------------------------------------------
		// Result
		// -------------------------------------------------------------------------------------------------
        AddResult("jrdn_gps_wire");//add results here
        m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
        m_ResultSetQuantity[0] = -1;//-1 = do nothing
        m_ResultSetHealth[0] = -1;//-1 = do nothing
        m_ResultInheritsHealth[0] = 0;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
        m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
        m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
        m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
        m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return true;
	}
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		super.Do(ingredients, player, results, specialty_weight);

		if (!GetGame() || !GetGame().IsServer())
			return;

		ItemBase tool    = ingredients[0];
		ItemBase target  = ingredients[1];
		ItemBase result0 = results[0];

		// 1) Read wetness from the target
		float wet_read;
		array<ItemBase> wet_sources = new array<ItemBase>;
		wet_sources.Insert(target);
		jrdn_helpers.ReadWet(wet_sources, wet_read);

		// 2) Preferred tool category (small blades for this recipe)
		array<toolCategory> preferredTools = new array<toolCategory>;
		preferredTools.Insert(toolCategory.TOOL_SMALL_BLADE);
		preferredTools.Insert(toolCategory.TOOL_LARGE_BLADE);
		toolCategory usedCat = GetToolCategory(tool);

		// 3) Wet-driven punishment (cuts/bleed)
		if (wet_read >= GameConstants.STATE_DAMP)
		{
			// Pull cut values directly from jrdn_settings
			float baseChance             = jrdn_settings.cut.baseChance;
			float wetnessScale           = jrdn_settings.cut.wetnessScale;
			float healthPenaltyAbs       = jrdn_settings.cut.healthPenaltyAbs;
			float preferredMultiplier    = jrdn_settings.tools.preferredMul;
			float notPreferredMultiplier = jrdn_settings.tools.notPreferredMul;

			bool didCut = jrdn_helpers.PunishCut(player, tool, preferredTools, wet_read, baseChance, wetnessScale, healthPenaltyAbs, preferredMultiplier, notPreferredMultiplier);

			if (didCut)
			{
				string usedSelection;
				jrdn_helpers.TryApplyBleedForTool(player, usedCat, usedSelection);
			}
		}

		// 4) Result punishment (wetness + wrong tool)
		float wetPenaltyAbs = 0.0;
		if (wet_read >= GameConstants.STATE_DAMP)
		{
			wetPenaltyAbs = Math.Clamp(wet_read * jrdn_settings.result.wetPenaltyScale, 0.0, jrdn_settings.result.wetPenaltyMax);
		}

		int powerType = 0; // not applicable for wire salvage

		jrdn_helpers.PunishResults(results, wet_read, GameConstants.STATE_DAMP, powerType, tool, preferredTools, wetPenaltyAbs, jrdn_settings.result.poweredPenaltyAbs,);

		// 5) Inherit wetness from target
		if (wet_read >= 0.0)
		{
			array<ItemBase> resArr = new array<ItemBase>;
			resArr.Insert(result0);
			jrdn_helpers.ApplyWet(resArr, wet_read);
		}

		// 6) Inherit health from target
		float inheritHealth;
		jrdn_helpers.ReadHealth(target, inheritHealth);
		if (inheritHealth >= 0.0)
			jrdn_helpers.ApplyHealth(result0, inheritHealth);
	}
};
class salvagePCBCasing extends RecipeBase
{
	override void Init()
	{
		// -------------------------------------------------------------------------------------------------
		// Common
		// -------------------------------------------------------------------------------------------------
		m_Name = "Salvage GPS parts";
		m_IsInstaRecipe = false;					// should this recipe be performed instantly without animation
		m_AnimationLength = 2;						// animation length in relative time units
		m_Specialty = 0;							// relates to the soft skills stats for players - recommended not to change
		//----------------------------------------------------------------------------------------------------------------------

		// -------------------------------------------------------------------------------------------------
		// Conditions
		// -------------------------------------------------------------------------------------------------
		m_MinDamageIngredient[0]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[0] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[0]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[0] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[0]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[0]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.
		m_MinDamageIngredient[1]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[1] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[1]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[1] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[1]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[1]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.

		// -------------------------------------------------------------------------------------------------
		// Ingredient 1
		// -------------------------------------------------------------------------------------------------
		// PreferredTools
		InsertIngredient(0, "Screwdriver");
		InsertIngredient(0, "Crowbar");
		InsertIngredient(0, "Pliers");

		// NotPreferredTools
		InsertIngredient(0, "SteakKnife");
		InsertIngredient(0, "KitchenKnife");
		InsertIngredient(0, "CombatKnife");
		InsertIngredient(0, "HuntingKnife");
		InsertIngredient(0, "Cleaver");
		InsertIngredient(0, "AK_Bayonet");
		InsertIngredient(0, "M9A1_Bayonet");
		InsertIngredient(0, "SNAFU_Kabar");
		InsertIngredient(0, "Msp_VorpalKnife");
		InsertIngredient(0, "KukriKnife");
		InsertIngredient(0, "FangeKnife");
		InsertIngredient(0, "Mosin_Bayonet");
		InsertIngredient(0, "SNAFU_SKS_Bayonet");
		InsertIngredient(0, "Machete");
		InsertIngredient(0, "CrudeMachete");
		InsertIngredient(0, "OrientalMachete");
		InsertIngredient(0, "Hatchet");
		InsertIngredient(0, "WoodAxe");
		InsertIngredient(0, "FirefighterAxe");
		InsertIngredient(0, "FirefighterAxe_Black");
		InsertIngredient(0, "FirefighterAxe_Green");
		InsertIngredient(0, "Pickaxe");
		InsertIngredient(0, "Iceaxe");
		InsertIngredient(0, "HandSaw");
		InsertIngredient(0, "Hacksaw");
		InsertIngredient(0, "Sword");
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
        m_IngredientSetHealth[0] = -1; // -1 = do nothing
        m_IngredientAddQuantity[0] = -1;// 0 = do nothing
        m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
        m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this 

		// -------------------------------------------------------------------------------------------------
		// Ingredient 2
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(1, "BaseRadio");
		InsertIngredient(1, "PersonalRadio");
		m_IngredientAddHealth[1] = -10;// 0 = do nothing
        m_IngredientSetHealth[1] = -1; // -1 = do nothing
        m_IngredientAddQuantity[1] = 0;// 0 = do nothing
        m_IngredientDestroy[1] = true;//true = destroy, false = do nothing
        m_IngredientUseSoftSkills[1] = false;// set 'true' to allow modification of the values by softskills on this ingredient

		// -------------------------------------------------------------------------------------------------
		// Result
		// -------------------------------------------------------------------------------------------------
        AddResult("jrdn_gps_pcb");//add results here
        m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
        m_ResultSetQuantity[0] = -1;//-1 = do nothing
        m_ResultSetHealth[0] = -1;//-1 = do nothing
        m_ResultInheritsHealth[0] = 1;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
        m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
        m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
        m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
        m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return true;
	}
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		super.Do(ingredients, player, results, specialty_weight);

		if (!GetGame() || !GetGame().IsServer())
			return;

		ItemBase tool    = ingredients[0];
		ItemBase target  = ingredients[1];
		ItemBase result0 = results[0];

		// 1) Build result pool and pick a class
		TStringArray resultPool = new TStringArray;
		resultPool.Insert("jrdn_gps_pcb");
		resultPool.Insert("jrdn_gps_case");
		resultPool.Insert("jrdn_gps_wired_pcb");

		string pickedClass;
		jrdn_helpers.RandomResults_Single(resultPool, pickedClass);
		if (pickedClass == "")
			return;

		// 2) Read wetness from ingredient[1]
		float wet_read;
		array<ItemBase> inheritWetFrom = new array<ItemBase>;
		inheritWetFrom.Insert(target);
		jrdn_helpers.ReadWet(inheritWetFrom, wet_read); // -1.0 if invalid

		// 3) Preferred tools (utility for electronics)
		array<toolCategory> preferredTools = new array<toolCategory>;
		preferredTools.Insert(toolCategory.TOOL_UTILITY);

		// 4) Spawn final result at feet with inheritance (health from target; wetness applied below)
		ItemBase finalResult = jrdn_helpers.KeepOrSpawnRandomResult(pickedClass, results, player, "", inheritWetFrom, target);
		if (!finalResult)
			return;

		// Ensure wetness is applied to the actual spawned item
		if (wet_read >= 0.0)
		{
			array<ItemBase> wetSingle = new array<ItemBase>;
			wetSingle.Insert(finalResult);
			jrdn_helpers.ApplyWet(wetSingle, wet_read);
		}

		// 5) Detect power and punish shock if powered
		ItemBase foundPower;
		int powerType = jrdn_helpers.DetectPoweredIngredient(target, foundPower);

		if (powerType > 0)
		{
			bool isCarType = true; // triggers fixed-target branch for car/truck inside PunishShock

			float base9V    		= jrdn_settings.power.base9V;
			float baseCar   		= jrdn_settings.power.baseCar;
			float baseTruck 		= jrdn_settings.power.baseTruck;
			float preferredMul      = jrdn_settings.tools.preferredMul;
			float notPreferredMul   = jrdn_settings.tools.notPreferredMul;
			float notPreferredFixed = jrdn_settings.tools.notPreferredFixed;

			jrdn_helpers.PunishShock(player, wet_read, powerType, tool, preferredTools, isCarType, base9V, baseCar, baseTruck, preferredMul, notPreferredMul, notPreferredFixed);
		}

		// 6) Punish result condition for wetness + wrong tool
		float wetPenaltyAbs = 0.0;
		if (wet_read >= GameConstants.STATE_DAMP)
		{
			wetPenaltyAbs = Math.Clamp(wet_read * jrdn_settings.result.wetPenaltyScale,0.0,jrdn_settings.result.wetPenaltyMax);
		}

		array<ItemBase> punishList = new array<ItemBase>;
		punishList.Insert(finalResult);

		jrdn_helpers.PunishResults(punishList, wet_read, GameConstants.STATE_DAMP, powerType, tool, preferredTools, wetPenaltyAbs, jrdn_settings.result.poweredPenaltyAbs, jrdn_settings.result.wrongToolPenaltyAbs);

		// 7) Optional ruin flags from settings
		if (finalResult)
		{
			if (powerType == 2 && jrdn_settings.result.ruinOnCarBattery)
			{
				finalResult.SetHealth("", "", 0.0);
			}
			else if (powerType == 3 && jrdn_settings.result.ruinOnTruckBattery)
			{
				finalResult.SetHealth("", "", 0.0);
			}
		}
	}
};
class craftWiredPCB extends RecipeBase
{
	override void Init()
	{
		// -------------------------------------------------------------------------------------------------
		// Common
		// -------------------------------------------------------------------------------------------------
		m_Name = "Combine wires and PCB";
		m_IsInstaRecipe = false;					// should this recipe be performed instantly without animation
		m_AnimationLength = 2;						// animation length in relative time units
		m_Specialty = 0;							// relates to the soft skills stats for players - recommended not to change

		// -------------------------------------------------------------------------------------------------
		// Conditions
		// -------------------------------------------------------------------------------------------------
		m_MinDamageIngredient[0]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[0] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[0]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[0] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[0]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[0]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.
		m_MinDamageIngredient[1]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[1] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[1]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[1] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[1]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[1]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.

		// -------------------------------------------------------------------------------------------------
		// Ingredient 1
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(0,"jrdn_gps_wire");
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = -1;// 0 = do nothing
		m_IngredientDestroy[0] = true;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this 

		// -------------------------------------------------------------------------------------------------
		// Ingredient 2
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(1, "jrdn_gps_pcb");
		m_IngredientAddHealth[1] = 0;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0; // 0 = do nothing
		m_IngredientDestroy[1] = true; //true = destroy, false = do nothing
		m_IngredientUseSoftSkills[1] = false; // set 'true' to allow modification of the values by softskills on this ingredient

		// -------------------------------------------------------------------------------------------------
		// Result
		// -------------------------------------------------------------------------------------------------
		AddResult("jrdn_gps_wired_pcb");//add results here
		m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
		m_ResultSetQuantity[0] = -1;//-1 = do nothing
		m_ResultSetHealth[0] = -1;//-1 = do nothing
		m_ResultInheritsHealth[0] = -2;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
		m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value

	}
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return jrdn_helpers.CanCombine_WetCheck(ingredients[0], ingredients[1]);
	}
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		super.Do(ingredients, player, results, specialty_weight);

		float Wet_Read;
		jrdn_helpers.ReadWet(ingredients, Wet_Read);

		if (GetGame() && GetGame().IsServer())
			jrdn_helpers.ApplyWet(results, Wet_Read);
	}
};
class craftGPS extends RecipeBase
{
	override void Init()
	{
		// -------------------------------------------------------------------------------------------------
		// Common
		// -------------------------------------------------------------------------------------------------
		m_Name = "Combine wires and PCB";
		m_IsInstaRecipe = false;					// should this recipe be performed instantly without animation
		m_AnimationLength = 2;						// animation length in relative time units
		m_Specialty = 0;							// relates to the soft skills stats for players - recommended not to change

		// -------------------------------------------------------------------------------------------------
		// Conditions
		// -------------------------------------------------------------------------------------------------
		m_MinDamageIngredient[0]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[0] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[0]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[0] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[0]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[0]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.
		m_MinDamageIngredient[1]		= -1;		// this checks the maximum condition an item can be when being repaired/crafted. if m_MinDamageIngredient[1] = 75, recipe won't trigger if ingredient condition = pristine. -1 = disabled.
		m_MaxDamageIngredient[1]		= 3;		// this checks the minimum condition an item can be when being repaired/crafted. if m_MaxDamageIngredient[1] = 10, recipe won't trigger if ingredient condition =< 10. 0=ruined, 100=pristine.
		m_MinQuantityIngredient[1]		= -1;		// the first ingredient must = this amount of item to be craftable. e.g. m_MinQuantityIngredient[0]=5; recipe needs 5 sticks to craft item, player has 4 sticks = can't craft. -1=disabled.
		m_MaxQuantityIngredient[1]		= -1;		// the first ingredient stack must = this amount of item to be craftable. e.g. m_MaxQuantityIngredient[0]=5; recipe needs 4 sticks to craft item, player has 6 sticks in stack = can't craft. -1=disabled.

		// -------------------------------------------------------------------------------------------------
		// Ingredient 1
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(0,"jrdn_gps_wired_pcb");
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = -1;// 0 = do nothing
		m_IngredientDestroy[0] = true;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this 

		// -------------------------------------------------------------------------------------------------
		// Ingredient 2
		// -------------------------------------------------------------------------------------------------
		InsertIngredient(1, "jrdn_gps_case");
		m_IngredientAddHealth[1] = 0;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0; // 0 = do nothing
		m_IngredientDestroy[1] = true; //true = destroy, false = do nothing
		m_IngredientUseSoftSkills[1] = false; // set 'true' to allow modification of the values by softskills on this ingredient

		// -------------------------------------------------------------------------------------------------
		// Result
		// -------------------------------------------------------------------------------------------------
		AddResult("GPSReceiver");//add results here
		m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
		m_ResultSetQuantity[0] = -1;//-1 = do nothing
		m_ResultSetHealth[0] = -1;//-1 = do nothing
		m_ResultInheritsHealth[0] = -2;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
		m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
	}
	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		if (!ingredients) return false;
		return jrdn_helpers.CanCombine_WetCheck(ingredients[0], ingredients[1]);
	}
	override void Do(ItemBase ingredients[], PlayerBase player, array<ItemBase> results, float specialty_weight)
	{
		super.Do(ingredients, player, results, specialty_weight);

		if (!ingredients) return;
		if (ingredients.Count() == 0) return;
		if (!results) return;

		float Wet_Read;
		jrdn_helpers.ReadWet(ingredients, Wet_Read);

		if (GetGame() && GetGame().IsServer())
			jrdn_helpers.ApplyWet(results, Wet_Read);
	}

};