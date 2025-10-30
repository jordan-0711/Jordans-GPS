// ===================================================================================
// jrdn_gps_settings.c
// Read-only global tuning values for Jordan's Recipe Mods.
// ===================================================================================
class jrdn_settings
{
    // ---------------------------------------------------------------------
    // Power bases for PunishShock
    // base9v/Car/Truck = player.AddHealth("", "Shock", 8.0/25.0/40.0);
    // baseMultiplyDamp/Wet/Soaking/Drenched = base9v(8.0) * baseMultiplyWet(1.50)
    // ---------------------------------------------------------------------
    static ref PowerSettings power = new PowerSettings;
    class PowerSettings
    {
        // base shock values
        float base9V    = 8.0;
        float baseCar   = 25.0;
        float baseTruck = 40.0;
        // shock health target values (used when isCarType == true)
        float baseDry = 50.0;  // base shock reduction when dry
        float baseWet = 20.0;  // base shock reduction when wet
        // shock wetness multipliers
        float baseMultiplyDry        = 1.0;  // Fallback when no wetness found
        float baseMultiplyDamp       = 1.25; // wetness >= STATE_DAMP < STATE_WET
        float baseMultiplyWet        = 1.50; // wetness >= STATE_WET < STATE_SOAKING_WET
        float baseMultiplySoaking    = 2.00; // wetness >= STATE_SOAKING_WET < STATE_DRENCHED
        float baseMultiplyDrenched   = 2.50; // wetness >= STATE_DRENCHED
    };
    // ---------------------------------------------------------------------
    // Cut punishment chance, chance when wet, and absolute damage
    // ---------------------------------------------------------------------
    static ref CutSettings cut = new CutSettings;
    class CutSettings
    {
        float baseChance       = 0.15; // base probability of a cut when conditions apply
        float wetnessScale     = 0.85; // scales chance by wetness (chance *= 1 + wet*wetnessScale)
        float healthPenaltyAbs = 5.0;  // absolute health damage to player on a successful cut
    };
    // ---------------------------------------------------------------------
    // Preferred tool multiplier settings
    // If true, recipes may reject crafting when wetness >= STATE_SOAKING_WET.
    // ---------------------------------------------------------------------
    static ref ToolSettings tools = new ToolSettings;
    class ToolSettings
    {
        float preferredMul          = 1.0;   // multiplier when using a preferred tool
        float notPreferredMul       = 1.35;  // multiplier when NOT using a preferred tool
        float notPreferredFixed     = -10.0; // static shock offset for non-preferred tools (car/truck shocks)
    };
    // ---------------------------------------------------------------------
    // Recipe wetness lockout
    // If true, recipes may reject crafting when wetness >= STATE_SOAKING_WET.
    // ---------------------------------------------------------------------
    static ref WetSettings wet = new WetSettings;
    class WetSettings
    {
        bool lockoutAtSoaking = true;
    };
    // ---------------------------------------------------------------------
    // Glove mitigation
    // ---------------------------------------------------------------------
    // static ref gloveMitigation yesGloves = new gloveMitigation;
    // class gloveMitigation
    // {
    //     bool gloveMitigation = 1;
    // };
    // ---------------------------------------------------------------------
    // Result damage tuning (used by salvageWires; available to others)
    // ---------------------------------------------------------------------
    static ref ResultSettings result = new ResultSettings;
    class ResultSettings
    {
        float wetPenaltyScale     = 4.0;  // result damage scales with wetness: wet * scale
        float wetPenaltyMax       = 10.0;  // cap for wet damage to result
        float wrongToolPenaltyAbs = 10.0;  // flat damage to result if tool not preferred
        float poweredPenaltyAbs   = 0.0;  // reserved (if you want result damage when powered)
        bool  ruinOnCarBattery    = true; // reserved convenience flag for powered recipes
        bool  ruinOnTruckBattery  = false;// reserved convenience flag for powered recipes
    };
};