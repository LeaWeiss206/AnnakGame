#include "NaturalLand.h"

NaturalLand::NaturalLand(int landTypeNumber)
{
    ReadJson json;
	landType = getCategoryBySelectedValue(landTypeNumber, "Tiles");
	this->landTypeNumber = landTypeNumber;
    rain = 0;
    this->resources = { 0,0,0,0 };
    if (landTypeNumber > 2)
        this->resources[landTypeNumber-3]= getValueBySelectedCategory(landType, "StartingResources");
}


 string NaturalLand::getCategoryBySelectedValue(int categ, string group)
{
     ReadJson json;
    unordered_map<string, int> items = json.getItems<string, int>(group);
    string key;
    for (auto& i : items) {
        if (i.second == categ) {
            key = i.first;
            break; // to stop searching
        }
    }
    return key;
}
 int NaturalLand::getValueBySelectedCategory(string categ, string group)
 {
     ReadJson json;
     unordered_map<string, int> items = json.getItems<string, int>(group);
     int value=-1;
     for (auto& i : items) {
         if (i.first == categ) {
             value = i.second;
             break; // to stop searching
         }
     }
     return value;
 }

 void NaturalLand::startResource(int amount)
 {
     this->resources[landTypeNumber - 3] = amount;
 }

 void NaturalLand::raining()
 {
     this->rain++;
     string resource;
     if (this->landType == "Forest")
         resource = "Wood";
     else
         resource = "Wool";
     int rainPerResource = getValueBySelectedCategory(resource, "Rains");
     if (this->rain >= rainPerResource) {
         this->resources[landTypeNumber - 3] += (this->rain / rainPerResource);
         this->rain= rain % rainPerResource;
     }
 }


