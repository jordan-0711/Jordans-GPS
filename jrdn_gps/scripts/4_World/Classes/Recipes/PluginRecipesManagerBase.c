modded class PluginRecipesManager
{
    override void RegisterRecipies()
    {
        super.RegisterRecipies();
        RegisterRecipe(new cutWires);
        RegisterRecipe(new salvagePCBCasing);
        RegisterRecipe(new createWiredPCB);
        RegisterRecipe(new createGPS);
    }
}