#include "pch.h"
#include "MapInfo.h"
#include "rapidcsv.h"

void MapInfo::LoadFromFile(std::string path)
{
	rapidcsv::Document doc(path);
	roomTexId = doc.GetCell<std::string>(1, 0);
	roomFloorTexId = doc.GetCell<std::string>(1, 1);

	for (int i = 2; i < doc.GetRowCount(); ++i)
	{
		std::vector<std::string> row = doc.GetRow<std::string>(i);

		if (row[0] == "mapObj")
		{
			MapObjectInfo info;
			info.objectType = row[0];                      //몬스터인지 mapObject인지 구분
			info.TexId = row[1];
			info.position.x = std::stof(row[2]);
			info.position.y = std::stof(row[3]);
			info.name = row[4];                            //ex) 폭탄으로 파괴가능한 rock인지 눈물로 파괴가능한 poop인지 구분
			objectList.push_back(info);
		}
		if (row[0] == "monster")
		{
			MonsterInfo info;
			info.monsterType = row[0];                     //몬스터인지 mapObject인지 구분
			info.TexId = row[1];
			info.position.x = std::stof(row[2]);
			info.position.y = std::stof(row[3]);
			info.name = row[4];                            //몬스터 종류 구분 : AttackFly, BoomFly, Charger, Dip, 등
			monsterList.push_back(info);

		}
	}
}

void MapInfo::SaveToFile(std::string path)
{
	rapidcsv::Document doc("", rapidcsv::LabelParams(-1, -1));

	std::vector<std::string> header = { "TYPE", "TEXTUREID", "X", "Y", "NAME" };
	doc.InsertRow(0, header);

	std::vector<std::string> room = { "Room", roomTexId, "0", "0", "room" };
	doc.InsertRow(1, room);

	std::vector<std::string> roomf = { "RoomFloor", roomFloorTexId, "0","0", "roomfloor"};
	doc.InsertRow(2, roomf);

	int row = 3;

	for (auto& obj : objectList)
	{
		std::vector<std::string> mapObject = { "mapObj", obj.TexId, std::to_string(obj.position.x),std::to_string(obj.position.y), obj.name};
		doc.InsertRow(row, mapObject);
		row++;
	}
	for (auto& go : monsterList)
	{
		std::vector<std::string> monster = { "monster", go.TexId, std::to_string(go.position.x), std::to_string(go.position.y), go.name};
		doc.InsertRow(row, monster);
		row++;
	}

	doc.Save(path);
}