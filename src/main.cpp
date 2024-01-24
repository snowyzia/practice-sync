#include <Geode/Geode.hpp>
#include <Geode/modify/GameStatsManager.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;


class $modify(PlayLayer) {
    GJGameLevel* gameLevel;
    bool init(GJGameLevel *p0, bool p1, bool p2) {
		auto enabledMod = Mod::get()->getSettingValue<bool>("mod-enabled");
        if (!PlayLayer::init(p0,p1,p2)) return false;
		if (enabledMod) {
 			GameStatsManager::sharedState()->toggleEnableItem(UnlockType::GJItem, 17, true);
		}
        return true;
    }
};

class $modify(GameStatsManager) {
    bool isItemUnlocked(UnlockType p0, int p1) {
		auto enabledMod = Mod::get()->getSettingValue<bool>("mod-enabled");
        if (p0 != UnlockType::GJItem && p1 != 17) return GameStatsManager::isItemUnlocked(p0,p1);
		// 17 and 18 are practice mode sync, 19 and 20 are main menu customisation???? i think.....
        if ((enabledMod) && (p1 == 17) || (p1 == 18)) {
            return true;
        } else {
            return GameStatsManager::isItemUnlocked(p0,p1);
        }
    }
};