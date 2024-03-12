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
			info.objectType = row[0];                      //�������� mapObject���� ����
			info.TexId = row[1];
			info.position.x = std::stof(row[2]);
			info.position.y = std::stof(row[3]);
			info.name = row[4];                            //ex) ��ź���� �ı������� rock���� ������ �ı������� poop���� ����
			objectList.push_back(info);
		}
		if (row[0] == "monster")
		{
			MonsterInfo info;
			info.monsterType = row[0];                     //�������� mapObject���� ����
			info.TexId = row[1];
			info.position.x = std::stof(row[2]);
			info.position.y = std::stof(row[3]);
			info.name = row[4];                            //���� ���� ���� : AttackFly, BoomFly, Charger, Dip, ��
			monsterList.push_back(info);

		}
	}
}