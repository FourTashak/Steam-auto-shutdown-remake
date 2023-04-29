#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <vector>
#include <Windows.h>

std::string GetSteamPath()
{
	HKEY hkey;
	std::string steam_path;

	if (RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\Valve\\Steam", 0, KEY_READ, &hkey) == ERROR_SUCCESS)
	{
		char path[MAX_PATH];
		DWORD path_size = sizeof(path);

		if (RegQueryValueEx(hkey, L"SteamPath", nullptr, nullptr, (LPBYTE)path, &path_size) == ERROR_SUCCESS)
		{
			for (int i = 0; i < path_size; i++)
			{
				if (path[i] != '\0')
					steam_path += path[i];
			}
		}

		RegCloseKey(hkey);
	}
	return steam_path;
}

void GetLibraryPaths(std::string steam_path, std::vector<std::string> &Paths)
{
	std::string Name = "appmanifest";
	std::string fname;
	steam_path += "\\steamapps\\libraryfolders.vdf";

	std::fstream libraryinfo;
	libraryinfo.open(steam_path, std::ios::in);


	if (libraryinfo.is_open())
	{
		std::string line;
		while (std::getline(libraryinfo, line))
		{
			if (line.find("path") != std::string::npos)
			{
				std::string Thispath = line.substr(11);
				Paths.push_back(Thispath.substr(0, (Thispath.size() - 1)) + "\\steamapps");
			}
		}
	}
}

void StoreStateFlagInfo(std::vector<std::string> &Paths, std::vector<std::string> &CheckPaths)
{
	std::string fname;
	std::string Name = "appmanifest";
	for (int i = 0; i < Paths.size(); i++)
	{
		std::filesystem::path path_to_list = Paths[i];
		for (const auto& entry : std::filesystem::directory_iterator(path_to_list))
		{
			std::string temp = entry.path().filename().string();
			fname = entry.path().string();
			temp.resize(Name.size());
			if (temp == Name)
			{
				std::fstream file;
				file.open(fname, std::ios::in);

				if (file.is_open())
				{
					std::string Line;
					std::string ToDownload;
					while (std::getline(file, Line))
					{
						if (Line.find("StateFlags") != std::string::npos)
						{
							ToDownload = Line.substr(16, Line.size());
							ToDownload.resize(ToDownload.size() - 1);
							if (std::stoi(ToDownload) == 1026 || std::stoi(ToDownload) == 1030)
							{
								CheckPaths.push_back(fname);
							}
						}
					}
				}
				file.close();
			}
		}
	}
}

void CheckStateFlags(std::vector<std::string> &CheckPaths)
{
	while (true)
	{
		for (int i = 0; i < CheckPaths.size(); i++)
		{
			std::fstream file;
			std::string line;
			file.open(CheckPaths[i], std::ios::in);
			std::string Stateflag;
			while (std::getline(file, line))
			{
				if (line.find("StateFlags") != std::string::npos)
				{
					Stateflag = line.substr(16, line.size());
					Stateflag.resize(Stateflag.size() - 1);
					if (std::stoi(Stateflag) == 4)
					{
						CheckPaths.erase(CheckPaths.begin() + i);
						if (CheckPaths.size() == 0)
						{
							system("shutdown -s");
						}
					}
				}
			}
		}
		Sleep(10000);
	}
}