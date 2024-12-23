#include "pch.h"

//JsonManager::JsonManager(const std::string& path) : mPath(path) {}
//
//bool JsonManager::LoadJson() {
//    std::ifstream file(mPath);
//    if (!file.is_open()) {
//        std::cerr << "Impossible d'ouvrir le fichier JSON: " << mPath << std::endl;
//        return false;
//    }
//
//    try {
//        file >> mJsonData;
//    }
//    catch (json::parse_error& e) {
//        std::cerr << "Erreur lors du parsing du fichier JSON: " << e.what() << std::endl;
//        return false;
//    }
//
//    file.close();
//    return true;
//}
//
//json JsonManager::GetPlayerStats(const std::string& playerName) const {
//    try {
//        return mJsonData.at("players").at(playerName);
//    }
//    catch (json::exception& e) {
//        std::cerr << "Erreur lors de l'accès aux données du joueur: " << e.what() << std::endl;
//        return nullptr;
//    }
//}