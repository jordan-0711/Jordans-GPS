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
		InsertIngredient(0, "KitchenKnife");
		InsertIngredient(0, "SteakKnife");
		InsertIngredient(0, "Cleaver");
		InsertIngredient(0, "CombatKnife");
		InsertIngredient(0, "HuntingKnife");
		InsertIngredient(0, "KukriKnife");
		InsertIngredient(0, "FangeKnife");
		InsertIngredient(0, "AK_Bayonet");
		InsertIngredient(0, "M9A1_Bayonet");
		InsertIngredient(0, "Mosin_Bayonet");
		InsertIngredient(0, "SNAFU_SKS_Bayonet");
		InsertIngredient(0, "Msp_VorpalKnife");
		InsertIngredient(0, "SNAFU_Kabar");
		InsertIngredient(0, "SNAFU_Kabar_BK");
		InsertIngredient(0, "Machete");
		InsertIngredient(0, "CrudeMachete");
		InsertIngredient(0, "OrientalMachete");
		InsertIngredient(0, "Hatchet");
		InsertIngredient(0, "WoodAxe");
		InsertIngredient(0, "FirefighterAxe");
		InsertIngredient(0, "HandSaw");
		InsertIngredient(0, "Hacksaw");
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
		float Wet_Read;
		jrdn_helpers.ReadWet(ingredients, Wet_Read);

		if (GetGame() && GetGame().IsServer())
		{
			// write same wetness to all results
			jrdn_helpers.ApplyWet(results, Wet_Read);

			// Optional: if you still want the “-10 damage when wet” punishment on the crafted items:
			if (Wet_Read >= GameConstants.STATE_WET)
			{
				for (int i = 0; i < results.Count(); i++)
				{
					ItemBase r = results[i];
					if (r) r.AddHealth("", "", -10.0);
				}
			}
		}
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
		InsertIngredient(0,"Screwdriver");
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
		// 1) 50/50 pick
		string pick;
		jrdn_gps_utils.RandomPickTwo("jrdn_gps_pcb", "jrdn_gps_case", pick);
		// 2) Inheritance from the dismantled device (ingredient 1)
		float inheritRatio;
		float inheritWet;
		jrdn_gps_utils.ReadInheritedState(ItemBase.Cast(ingredients[1]), inheritRatio, inheritWet);
		// 3) Keep placeholder PCB or spawn chosen item; always apply inheritance
		jrdn_gps_utils.KeepOrSpawnResult(pick, results, player, inheritRatio, inheritWet, "jrdn_gps_pcb");
		// 4) Shock if powered (no stamina), drops item in hands, message
		jrdn_gps_utils.ShockIfPowered(ItemBase.Cast(ingredients[1]), player);
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