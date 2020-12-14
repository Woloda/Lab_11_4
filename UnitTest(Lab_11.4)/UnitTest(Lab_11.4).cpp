#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_11.4/Lab_11.4.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab114
{
	TEST_CLASS(UnitTestLab114)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			towar s;
			towar str;
			towar str_a;
			towar str_b;
			fstream f;

			fstream file_s("E:\\Моя папка. Навчання\\Student [IK-11] [Дорожовець]\\Lab_11.4\Lab_11.4\\test", ios::binary);

			s.n_towar = "SDFSD";
			s.vartіst = 120;
			s.kilkist = 20;
			s.units = (measurement)2;
			s.masa = 10;

			s.n_towar = "SDDDSD";
			s.vartіst = 90;
			s.kilkist = 20;
			s.units = (measurement)2;
			s.masa = 10;

			s.n_towar = "SDFSD";
			s.vartіst = 80;
			s.kilkist = 20;
			s.units = (measurement)2;
			s.masa = 10;

			file_s.write((char*)&s, sizeof(towar));
			file_s.close();

			SortBIN(str, str_a, str_b, 3, "E:\\Моя папка. Навчання\\Student [IK-11] [Дорожовець]\\Lab_11.4\Lab_11.4\\test", f, false);
			
			file_s.read((char*)&s, sizeof(towar));
			Assert::AreEqual(s.vartіst, 80);
			file_s.close();
		}
	};
}
