#pragma once
class MapLoader
{
private:
	unsigned int load(char* path);

public:
	int ImgArray[256][256];
	unsigned char* RGBAPixelData;
	MapLoader(char* path);
	~MapLoader();
};
