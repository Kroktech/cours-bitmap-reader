#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>
using uint8 = unsigned char;
class Bitmap
{
public:
	Bitmap(const int& width = 0, const int& height = 0) :
		m_width(width)
		, m_height(height)
	{

	}
	struct Rgb
	{
		explicit Rgb(const uint8& r =0, const uint8& g=0,const uint8& b=0)
		{
			pixel[0] = r;
			pixel[1] = g;
			pixel[2] = b;
		}
		uint8 pixel[3];
	};
	int getHeaderSize() const
	{
		return sizeof(m_fileheader) + sizeof(m_DIBheader);
	}
	int getfilesize() const
	{
		return getHeaderSize() + getImageSize();
	}
	int getImageSize() const
	{
		const int size = m_width * m_height;
		return 3 * size;

	}
	void setData(Rgb* data, const int& size)
	{
		m_data.clear();
		m_data.resize(size);
		for (auto i = 0; i < size; ++i)
			m_data[i] = data[i];
		updateFIleHeader();

	}
	bool save(const std::string& filename)
	{
		std::ofstream file(filename, std::ios::binary);
		if (!file.is_open())
			return false;

		file.write(reinterpret_cast<char*>(&m_fileheader[0]),14);
		file.write(reinterpret_cast<char*>(&m_fileheader[0]), 40);
		file.close();
		return true;
	}
	int getPpm()
	{
		return 72 * 39;
	}
private:

	void updateFIleHeader()
	{
		static const int start = 2;
		const auto fileSize = getfilesize();
		for (auto i = start; i < start + 4; ++i)
			m_fileheader[i] = static_cast<uint8>(fileSize >> (i - start) * 8);

	}
	void updateDIBHeader()
	{
		// width
		static const int startwidth = 4;
		for (auto i = startwidth; i < startwidth + 4; ++i)
			m_fileheader[i] = static_cast<uint8>(m_width >> (i - startwidth) * 8);

		//height
		static const int startheight = 8;
		for (auto i = startheight; i < startheight + 4; ++i)
			m_fileheader[i] = static_cast<uint8>(m_height >> (i - startheight) * 8);

		//image size 
		static const int startimagesize = 20;
		for (auto i = startimagesize; i < startimagesize + 4; ++i)
			m_fileheader[i] = static_cast<uint8>(getImageSize() >> (i - startimagesize) * 8);

		// horizontale rez
		static const int startrezolutionh = 24;
		for (auto i = startrezolutionh; i < startrezolutionh + 4; ++i)
			m_fileheader[i] = static_cast<uint8>(getPpm() >> (i - startrezolutionh) * 8);

		//vertical rez 
		static const int startrezolutionv = 28;
		for (auto i = startrezolutionv; i < startrezolutionv + 4; ++i)
			m_fileheader[i] = static_cast<uint8>(getPpm() >> (i - startrezolutionv) * 8);
	}

	uint8 m_fileheader[14] = {
	'B', 'M',  // id 
	0,0,0,0, //size
	0,0,//reserved
	0,0,//reserver
	54,0,0,0//offset
	};
	uint8 m_DIBheader[40] = {
		40,0,0,0, //size of the header
		0,0,0,0, // width
		0,0,0,0, // height
		1,0, // num color plane
		24,0, // bits per seconde 
		0,0,0,0, // compression default
		0,0,0,0, // image size 
		0,0,0,0, //horizontale rez
		0,0,0,0, // vertical rez
		0,0,0,0, //number of color
		0,0,0,0, // important colors without preferences
	};
	int m_width;
	int m_height;
	std::vector<Rgb> m_data;

};

int main()
{
	Bitmap bmp(2, 2);
	Bitmap::Rgb color[4] =
	{
		Bitmap::Rgb{255,0,0},
		Bitmap::Rgb{0,255,0},
		Bitmap::Rgb{0,0,255},
		Bitmap::Rgb{255,255,255}
	};

	bmp.setData(color, 4);
	bmp.save("C:\\image\\test.bmp");
	// decalage d'octet 

}
