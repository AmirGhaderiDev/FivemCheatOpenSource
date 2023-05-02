#pragma once
#include <Windows.h>
#include <string>

static std::wstring get_weapon_name(DWORD hash)
{
	//removed xoring, cba to do properly.
	static auto upnatomizer = std::wstring(L"up-n atomizer");
	static auto dagger = std::wstring(L"dagger");
	static auto bat = std::wstring(L"bat");
	static auto bottle = std::wstring(L"bottle");
	static auto crowbar = std::wstring(L"crowbar");
	static auto unarmed = std::wstring(L"unarmed");
	static auto flashlight = std::wstring(L"flashlight");
	static auto golfclub = std::wstring(L"golfclub");
	static auto hammer = std::wstring(L"hammer");
	static auto hatchet = std::wstring(L"hatchet");
	static auto knuckle = std::wstring(L"knuckle");
	static auto knife = std::wstring(L"knife");
	static auto machete = std::wstring(L"machete");
	static auto switchblade = std::wstring(L"switchblade");
	static auto nightstick = std::wstring(L"nightstick");
	static auto wrench = std::wstring(L"wrench");
	static auto battleaxe = std::wstring(L"battleaxe");
	static auto poolcue = std::wstring(L"poolcue");
	static auto pistol = std::wstring(L"pistol");
	static auto pistolmk2 = std::wstring(L"pistol_mk2");
	static auto combatpistol = std::wstring(L"combatpistol");
	static auto appistol = std::wstring(L"appistol");
	static auto stungun = std::wstring(L"stungun");
	static auto pistol50 = std::wstring(L"pistol50");
	static auto snspistol = std::wstring(L"snspistol");
	static auto snspistolmk2 = std::wstring(L"snspistol_mk2");
	static auto heavypistol = std::wstring(L"heavypistol");
	static auto vintagepistol = std::wstring(L"vintagepistol");
	static auto flaregun = std::wstring(L"flaregun");
	static auto marksmanpistol = std::wstring(L"marksmanpistol");
	static auto revolver = std::wstring(L"revolver");
	static auto revolvermk2 = std::wstring(L"revolver_mk2");
	static auto doubleaction = std::wstring(L"doubleaction");
	static auto microsmg = std::wstring(L"microsmg");
	static auto smg = std::wstring(L"smg");
	static auto smgmk2 = std::wstring(L"smg_mk2");
	static auto assaultsmg = std::wstring(L"assaultsmg");
	static auto combatpdw = std::wstring(L"combatpdw");
	static auto machinepistol = std::wstring(L"machinepistol");
	static auto minismg = std::wstring(L"minismg");
	static auto pumpshotgun = std::wstring(L"pumpshotgun");
	static auto pumpshotgun_mk2 = std::wstring(L"pumpshotgun_mk2");
	static auto sawnoffshotgun = std::wstring(L"sawnoffshotgun");
	static auto assaultshotgun = std::wstring(L"assaultshotgun");
	static auto bullpupshotgun = std::wstring(L"bullpupshotgun");
	static auto musket = std::wstring(L"musket");
	static auto heavyshotgun = std::wstring(L"heavyshotgun");
	static auto dbshotgun = std::wstring(L"dbshotgun");
	static auto autoshotgun = std::wstring(L"autoshotgun");
	static auto assaultrifle = std::wstring(L"assaultrifle");
	static auto assaultrifle_mk2 = std::wstring(L"assaultrifle_mk2");
	static auto carbinerifle = std::wstring(L"carbinerifle");
	static auto carbinerifle_mk2 = std::wstring(L"carbinerifle_mk2");
	static auto advancedrifle = std::wstring(L"advancedrifle");
	static auto specialcarbine = std::wstring(L"specialcarbine");
	static auto specialcarbine_mk2 = std::wstring(L"specialcarbine_mk2");
	static auto bullpuprifle = std::wstring(L"bullpuprifle");
	static auto bullpuprifle_mk2 = std::wstring(L"bullpuprifle_mk2");
	static auto compactrifle = std::wstring(L"compactrifle");
	static auto machine_gun = std::wstring(L"machine_gun");
	static auto combatmg = std::wstring(L"combatmg");
	static auto combatmg_mk2 = std::wstring(L"combatmg_mk2");
	static auto gusenberg = std::wstring(L"gusenberg");
	static auto unholyhellbringer = std::wstring(L"unholy hellbringer");
	static auto sniperrifle = std::wstring(L"sniperrifle");
	static auto heavysniper = std::wstring(L"heavysniper");
	static auto heavysniper_mk2 = std::wstring(L"heavysniper_mk2");
	static auto marksmanrifle = std::wstring(L"marksmanrifle");
	static auto marksmanrifle_mk2 = std::wstring(L"marksmanrifle_mk2");
	static auto rpg = std::wstring(L"rpg");
	static auto grenadelauncher = std::wstring(L"grenadelauncher");
	static auto grenadelauncher_smoke = std::wstring(L"grenadelauncher_smoke");
	static auto minigun = std::wstring(L"minigun");
	static auto widowmaker = std::wstring(L"widowmaker");
	static auto firework = std::wstring(L"firework");
	static auto railgun = std::wstring(L"railgun");
	static auto hominglauncher = std::wstring(L"hominglauncher");
	static auto compactlauncher = std::wstring(L"compactlauncher");
	static auto grenade = std::wstring(L"grenade");
	static auto bzgas = std::wstring(L"bzgas");
	static auto smokegrenade = std::wstring(L"smokegrenade");
	static auto flare = std::wstring(L"flare");
	static auto molotov = std::wstring(L"molotov");
	static auto stickybomb = std::wstring(L"stickybomb");
	static auto proxmine = std::wstring(L"proxmine");
	static auto snowball = std::wstring(L"snowball");
	static auto pipebomb = std::wstring(L"pipebomb");
	static auto ball = std::wstring(L"ball");
	static auto petrolcan = std::wstring(L"petrolcan");
	static auto fireextinguisher = std::wstring(L"fireextinguisher");
	static auto parachute = std::wstring(L"parachute");

	switch (hash)
	{
	case 2939590305:
		return upnatomizer.c_str(); break;
	case 2460120199:
		return dagger.c_str(); break;
	case 2508868239:
		return bat.c_str(); break;
	case 4192643659:
		return bottle.c_str(); break;
	case 2227010557:
		return crowbar.c_str(); break;
	case 2725352035:
		return unarmed.c_str(); break;
	case 2343591895:
		return flashlight.c_str(); break;
	case 1141786504:
		return golfclub.c_str(); break;
	case 1317494643:
		return hammer.c_str(); break;
	case 4191993645:
		return hatchet.c_str(); break;
	case 3638508604:
		return knuckle.c_str(); break;
	case 2578778090:
		return knife.c_str(); break;
	case 3713923289:
		return machete.c_str(); break;
	case 3756226112:
		return switchblade.c_str(); break;
	case 1737195953:
		return nightstick.c_str(); break;
	case 419712736:
		return wrench.c_str(); break;
	case 3441901897:
		return battleaxe.c_str(); break;
	case 2484171525:
		return poolcue.c_str(); break;
	case 453432689:
		return pistol.c_str(); break;
	case 3219281620:
		return pistolmk2.c_str(); break;
	case 1593441988:
		return combatpistol.c_str(); break;
	case 584646201:
		return appistol.c_str(); break;
	case 911657153:
		return stungun.c_str(); break;
	case 2578377531:
		return pistol50.c_str(); break;
	case 3218215474:
		return snspistol.c_str(); break;
	case 2285322324:
		return snspistolmk2.c_str(); break;
	case 3523564046:
		return heavypistol.c_str(); break;
	case 137902532:
		return vintagepistol.c_str(); break;
	case 1198879012:
		return flaregun.c_str(); break;
	case 3696079510:
		return marksmanpistol.c_str(); break;
	case 3249783761:
		return revolver.c_str(); break;
	case 3415619887:
		return revolvermk2.c_str(); break;
	case 2548703416:
		return doubleaction.c_str(); break;
	case 324215364:
		return microsmg.c_str(); break;
	case 736523883:
		return smg.c_str(); break;
	case 2024373456:
		return smgmk2.c_str(); break;
	case 4024951519:
		return assaultsmg.c_str(); break;
	case 171789620:
		return combatpdw.c_str(); break;
	case 3675956304:
		return machinepistol.c_str(); break;
	case 3173288789:
		return minismg.c_str(); break;
	case 487013001:
		return pumpshotgun.c_str(); break;
	case 1432025498:
		return pumpshotgun_mk2.c_str(); break;
	case 2017895192:
		return sawnoffshotgun.c_str(); break;
	case 3800352039:
		return assaultshotgun.c_str(); break;
	case 2640438543:
		return bullpupshotgun.c_str(); break;
	case 2828843422:
		return musket.c_str(); break;
	case 984333226:
		return heavyshotgun.c_str(); break;
	case 4019527611:
		return dbshotgun.c_str(); break;
	case 317205821:
		return autoshotgun.c_str(); break;
	case 3220176749:
		return assaultrifle.c_str(); break;
	case 961495388:
		return assaultrifle_mk2.c_str(); break;
	case 2210333304:
		return carbinerifle.c_str(); break;
	case 4208062921:
		return carbinerifle_mk2.c_str(); break;
	case 2937143193:
		return advancedrifle.c_str(); break;
	case 3231910285:
		return specialcarbine.c_str(); break;
	case 2526821735:
		return specialcarbine_mk2.c_str(); break;
	case 2132975508:
		return bullpuprifle.c_str(); break;
	case 2228681469:
		return bullpuprifle_mk2.c_str(); break;
	case 1649403952:
		return compactrifle.c_str(); break;
	case 2634544996:
		return machine_gun.c_str(); break;
	case 2144741730:
		return combatmg.c_str(); break;
	case 3686625920:
		return combatmg_mk2.c_str(); break;
	case 1627465347:
		return gusenberg.c_str(); break;
	case 1198256469:
		return unholyhellbringer.c_str(); break;
	case 100416529:
		return sniperrifle.c_str(); break;
	case 205991906:
		return heavysniper.c_str(); break;
	case 177293209:
		return heavysniper_mk2.c_str(); break;
	case 3342088282:
		return marksmanrifle.c_str(); break;
	case 1785463520:
		return marksmanrifle_mk2.c_str(); break;
	case 2982836145:
		return rpg.c_str(); break;
	case 2726580491:
		return grenadelauncher.c_str(); break;
	case 1305664598:
		return grenadelauncher_smoke.c_str(); break;
	case 1119849093:
		return minigun.c_str(); break;
	case 3056410471:
		return widowmaker.c_str(); break;
	case 2138347493:
		return firework.c_str(); break;
	case 1834241177:
		return railgun.c_str(); break;
	case 1672152130:
		return hominglauncher.c_str(); break;
	case 125959754:
		return compactlauncher.c_str(); break;
	case 2481070269:
		return grenade.c_str(); break;
	case 2694266206:
		return bzgas.c_str(); break;
	case 4256991824:
		return smokegrenade.c_str(); break;
	case 1233104067:
		return flare.c_str(); break;
	case 615608432:
		return molotov.c_str(); break;
	case 741814745:
		return stickybomb.c_str(); break;
	case 2874559379:
		return proxmine.c_str(); break;
	case 126349499:
		return snowball.c_str(); break;
	case 3125143736:
		return pipebomb.c_str(); break;
	case 600439132:
		return ball.c_str(); break;
	case 883325847:
		return petrolcan.c_str(); break;
	case 101631238:
		return fireextinguisher.c_str(); break;
	case 4222310262:
		return parachute.c_str(); break;
	default:
		return unarmed.c_str(); break;
	}
}