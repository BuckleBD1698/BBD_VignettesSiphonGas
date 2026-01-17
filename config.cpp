class CfgPatches
{
	class BBD_VignettesSiphonGas
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class BBD_VignettesSiphonGas_Mod
	{
		dir 		= "BBD_VignettesSiphonGas";
		name 		= "Vignettes Siphon Fuel";
		author 		= "BuckleBD";
		credits 	= "";
		creditsJSON = "";
		version 	= 1.0.0;
		extra 		= 0;
		type 		= "mod";
		inputs 		= "";
		picture 	= "";
		logo 		= "";
		logoSmall 	= "";
		logoOver 	= "";
		action 		= "";

		dependencies[] = {"Game","World","Mission"};
		
		class defs
		{
			class gameScriptModule
			{
				value = "";
				files[] = {"BBD_VignettesSiphonGas/scripts/3_game"};
			};
			class worldScriptModule
			{
				value = "";
				files[] = {"BBD_VignettesSiphonGas/scripts/4_world"};
			};
			class missionScriptModule
			{
				value = "";
				files[] = {"BBD_VignettesSiphonGas/scripts/5_mission"};
			};
		};
	};
};