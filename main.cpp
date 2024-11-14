//#include <iostream>
//#include <vector>
//#include <cstdint>
//#include <string>
//#include <fstream>
//using uint8 = unsigned char;
//class Bitmap
//{
//public:
//	Bitmap(const int& width = 0, const int& height = 0) :
//		m_width(width)
//		, m_height(height)
//	{
//
//	}
//	struct Rgb
//	{
//		explicit Rgb(const uint8& r = 0, const uint8& g = 0, const uint8& b = 0)
//		{
//			pixel[0] = r;
//			pixel[1] = g;
//			pixel[2] = b;
//		}
//		uint8 pixel[3];
//	};
//	int getHeaderSize() const
//	{
//		return sizeof(m_fileheader) + sizeof(m_DIBheader);
//	}
//	int getfilesize() const
//	{
//		return getHeaderSize() + getImageSize();
//	}
//	int getImageSize() const
//	{
//		const int size = m_width * m_height;
//		return 3 * size;
//
//	}
//	void setData(Rgb* data, const int& size)
//	{
//		m_data.clear();
//		m_data.resize(size);
//		for (auto i = 0; i < size; ++i)
//			m_data[i] = data[i];
//		updateFIleHeader();
//
//	}
//	bool save(const std::string& filename)
//	{
//		std::ofstream file(filename, std::ios::binary);
//		if (!file.is_open())
//			return false;
//
//		file.write(reinterpret_cast<char*>(&m_fileheader[0]), 14);
//		file.write(reinterpret_cast<char*>(&m_fileheader[0]), 40);
//		for (int i = 0; i < m_height; ++i)
//		{
//			for (int j = 0; j < m_width; ++j)
//			{
//				const auto& pixel = m_data[(m_height - i - 1) * m_width + j];
//				file.write(reinterpret_cast<const char*>(&pixel.pixel[0]), 3); // 3 bytes per pixel (RGB)
//			}
//		}
//
//		file.close();
//		return true;
//	}
//	int getPpm()
//	{
//		return 72 * 39;
//	}
//private:
//
//	void updateFIleHeader()
//	{
//		static const int start = 2;
//		const auto fileSize = getfilesize();
//		for (auto i = start; i < start + 4; ++i)
//			m_fileheader[i] = static_cast<uint8>(fileSize >> (i - start) * 8);
//
//	}
//	void updateDIBHeader()
//	{
//		// width
//		static const int startwidth = 4;
//		for (auto i = startwidth; i < startwidth + 4; ++i)
//			m_DIBheader[i] = static_cast<uint8>(m_width >> (i - startwidth) * 8);
//
//		//height
//		static const int startheight = 8;
//		for (auto i = startheight; i < startheight + 4; ++i)
//			m_DIBheader[i] = static_cast<uint8>(m_height >> (i - startheight) * 8);
//
//		//image size 
//		static const int startimagesize = 20;
//		for (auto i = startimagesize; i < startimagesize + 4; ++i)
//			m_DIBheader[i] = static_cast<uint8>(getImageSize() >> (i - startimagesize) * 8);
//
//		// horizontale rez
//		static const int startrezolutionh = 24;
//		for (auto i = startrezolutionh; i < startrezolutionh + 4; ++i)
//			m_DIBheader[i] = static_cast<uint8>(getPpm() >> (i - startrezolutionh) * 8);
//
//		//vertical rez 
//		static const int startrezolutionv = 28;
//		for (auto i = startrezolutionv; i < startrezolutionv + 4; ++i)
//			m_DIBheader[i] = static_cast<uint8>(getPpm() >> (i - startrezolutionv) * 8);
//	}
//
//	uint8 m_fileheader[14] = {
//	'B', 'M',  // id 
//	0,0,0,0, //size
//	0,0,//reserved
//	0,0,//reserver
//	54,0,0,0//offset
//	};
//	uint8 m_DIBheader[40] = {
//		40,0,0,0, //size of the header
//		0,0,0,0, // width
//		0,0,0,0, // height
//		1,0, // num color plane
//		24,0, // bits per seconde 
//		0,0,0,0, // compression default
//		0,0,0,0, // image size 
//		0,0,0,0, //horizontale rez
//		0,0,0,0, // vertical rez
//		0,0,0,0, //number of color
//		0,0,0,0, // important colors without preferences
//	};
//	int m_width;
//	int m_height;
//	std::vector<Rgb> m_data;
//
//};
//
//int main()
//{
//	Bitmap bmp(2, 2);
//	Bitmap::Rgb color[4] =
//	{
//		Bitmap::Rgb{255,0,0},
//		Bitmap::Rgb{0,255,0},
//		Bitmap::Rgb{0,0,255},
//		Bitmap::Rgb{255,255,255}
//	};
//
//	bmp.setData(color, 4);
//	bmp.save("C:\\image\\test.bmp");
//	// decalage d'octet 
//
//}
#include <iostream>
#include <vector>
#include <cstdint>
#include <string>
#include <fstream>

using uint8 = unsigned char;

class Bitmap {
public:
    Bitmap(const int& width = 0, const int& height = 0)
        : m_width(width), m_height(height) {}

    struct Rgb {
        explicit Rgb(const uint8& r = 0, const uint8& g = 0, const uint8& b = 0) {
            pixel[0] = r;
            pixel[1] = g;
            pixel[2] = b;
        }
        uint8 pixel[3];
    };

    int getHeaderSize() const {
        return sizeof(m_fileheader) + sizeof(m_DIBheader);
    }

    int getfilesize() const {
        return getHeaderSize() + getImageSizewidthpadding();
    }

    int getImageSizewidthpadding() const {
        const int size = 3 * m_width + getPaddingSize();
        return  m_height * size;
    }

    // Met à jour les données du bitmap avec les pixels
    void setData(Rgb* data, const int& size) {
        m_data.clear();
        m_data.resize(size);
        for (auto i = 0; i < size; ++i)
            m_data[i] = data[i];

    }
    void savePixel(std::ofstream& file)
    {
        for (int row = m_height - 1; row >= 0; --row) {
            for (int col = 0; col < m_width; ++col) {
                //const auto& pixel = m_data[(m_height - i - 1) * m_width + j/* j*m_height+i*/];
                //file.write(reinterpret_cast<const char*>(&pixel.pixel[0]), 3); // 3 octets par pixel (RGB)
                Rgb writepixel = m_data[row * m_width + col];
                file.write(reinterpret_cast<const char*>(&writepixel.pixel[2]), 1);
                file.write(reinterpret_cast<const char*>(&writepixel.pixel[1]), 1);
                file.write(reinterpret_cast<const char*>(&writepixel.pixel[0]), 1);

            }
            // Ajouter le padding à la fin de chaque ligne pour l'aligner sur 4 octets
            addPadding(file);
        }
       
    }

    // Sauvegarde le bitmap dans un fichier
    bool save(const std::string& filename) {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open())
            return false;

        // Met à jour les en-têtes

        updateFIleHeader();
        updateDIBHeader();

        // Écrit l'en-tête du fichier (14 octets)
        file.write(reinterpret_cast<char*>(m_fileheader), 14);

        // Écrit l'en-tête DIB (40 octets)
        file.write(reinterpret_cast<char*>(m_DIBheader), 40);

        // Écrire les données des pixels

        savePixel(file);
        file.close();
        return true;
    }

private:
    // Met à jour l'en-tête du fichier (file header)
    void updateFIleHeader() {
        static const int start = 2;
        const auto fileSize = getfilesize();
        for (auto i = start; i < start + 4; ++i)
            m_fileheader[i] = static_cast<uint8>(fileSize >> (i - start) * 8);
    }

    // Met à jour l'en-tête DIB (DIB header)
    void updateDIBHeader() {
        // largeur
        static const int startwidth = 4;
        for (auto i = startwidth; i < startwidth + 4; ++i)
            m_DIBheader[i] = static_cast<uint8>(m_width >> (i - startwidth) * 8);

        // hauteur
        static const int startheight = 8;
        for (auto i = startheight; i < startheight + 4; ++i)
            m_DIBheader[i] = static_cast<uint8>(m_height >> (i - startheight) * 8);

        // taille de l'image
        static const int startimagesize = 20;
        for (auto i = startimagesize; i < startimagesize + 4; ++i)
            m_DIBheader[i] = static_cast<uint8>(getImageSizewidthpadding() >> (i - startimagesize) * 8);

        // résolution horizontale
        static const int startrezolutionh = 24;
        for (auto i = startrezolutionh; i < startrezolutionh + 4; ++i)
            m_DIBheader[i] = static_cast<uint8>(getPpm() >> (i - startrezolutionh) * 8);

        // résolution verticale
        static const int startrezolutionv = 28;
        for (auto i = startrezolutionv; i < startrezolutionv + 4; ++i)
            m_DIBheader[i] = static_cast<uint8>(getPpm() >> (i - startrezolutionv) * 8);
    }

    // Calcule le padding nécessaire pour que la ligne de pixels soit un multiple de 4
    int getPaddingSize() const {
        int rowSize = m_width * 3; // chaque pixel fait 3 octets
        int padding = (4 - (rowSize % 4)) % 4;
        return padding;
    }

    // Ajoute le padding à la fin d'une ligne
    void addPadding(std::ofstream& file) {
        int padding = getPaddingSize();
        for (int i = 0; i < padding; ++i)
            file.put(0);  // Écrire 0x00 comme padding
    }

    uint8 m_fileheader[14] = {
        'B', 'M',  // ID du fichier BMP
        0, 0, 0, 0, // Taille du fichier
        0, 0, // Réservé
        0, 0, // Réservé
        54, 0, 0, 0 // Décalage vers les données des pixels
    };

    uint8 m_DIBheader[40] = {
        40, 0, 0, 0, // Taille de l'en-tête DIB
        0, 0, 0, 0,  // Largeur
        0, 0, 0, 0,  // Hauteur
        1, 0, // Nombre de plans de couleur
        24, 0, // Bits par pixel (24 = RGB)
        0, 0, 0, 0, // Compression (aucune)
        0, 0, 0, 0, // Taille de l'image (calculée plus tard)
        0, 0, 0, 0, // Résolution horizontale
        0, 0, 0, 0, // Résolution verticale
        0, 0, 0, 0, // Nombre de couleurs (0 pour 24 bits)
        0, 0, 0, 0  // Couleurs importantes (0 pour toutes)
    };

    int m_width;
    int m_height;
    std::vector<Rgb> m_data;

    int getPpm() {
        return static_cast<int>(72 * 39, 3701); // Résolution en pixels par pouce (juste un exemple)
    }
};

int main() {
    Bitmap bmp(2, 2);
    Bitmap::Rgb color[4] = {
        Bitmap::Rgb{0, 0, 255},// Bleu
        Bitmap::Rgb{0, 255, 0},  // Vert
        Bitmap::Rgb{255, 0, 0},  // Rouge


        Bitmap::Rgb{255, 255, 255} // Blanc
    };

    bmp.setData(color, 4);
    bmp.save("C:\\image\\test.bmp");

    return 0;
}
