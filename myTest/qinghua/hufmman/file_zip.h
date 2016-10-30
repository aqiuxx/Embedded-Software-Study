//文件压缩与解压
#pragma once
#include<iostream>
#include<string>
using namespace std;
#include"HuffmanTree.h"

struct CharInfo
{
	unsigned char _ch;
	long _count;
	string _code;
	CharInfo(const long count = 0)
		:_count(count)
	{}
	CharInfo(const unsigned char ch)
		:_ch(ch)
	{}
	long operator+(const CharInfo& info)const
	{
		return _count + info._count;
	}
	bool operator!=(const CharInfo& info)const
	{
		return _count != info._count;
	}
	bool operator<(const CharInfo& info)const
	{
		return _count < info._count;
	}
};
class FileCompress
{
public:
	//对文件filename进行压缩
	void Compress(const char* filename)
	{
		FILE* fread = fopen(filename, "rb");
		if (fread == NULL)
		{
			cout << "打开文件失败..." << endl;
			return;
		}
		//打开文件成功
		//1、字符与下标对应,填充结构体的_ch
		for (int i = 0; i < 256; i++)
		{
			_Info[i]._ch = i;
		}

		//2、统计各个字符出现的次数
		unsigned char ch = fgetc(fread);
		while (!feof(fread))
		{
			_Info[ch]._count++;
			ch = fgetc(fread);
		}

		//3、建立哈夫曼树
		HuffmanTree<CharInfo> hft(_Info, 256, CharInfo());

		//4、获取各个字符的哈夫曼编码
		//每次都从根节点开始，走到叶节点，即得到叶节点对应字符的编码
		HuffmanTreeNode<CharInfo>*root = hft.GetRoot();
		string code;
		GetHuffmanCodeOfChar(root, code);

	


		//5、从头开始读文件，把读取字符的编码重新组合写入压缩文件中
		fseek(fread, 0, SEEK_SET);
		//压缩产生的文件的名字
		string fcp = filename;
		fcp += ".compress";
		FILE* fwrite = fopen(fcp.c_str(), "wb");
		if (fwrite == NULL)
		{
			cout << "compress 文件打开失败" << endl;
			return;
		}

		//打开文件成功
		unsigned char data = 0;//写入压缩文件的字符
		int offset = 7;//偏移量
		ch = fgetc(fread);
		while (!feof(fread))
		{
			const char* str = _Info[ch]._code.c_str();//获取当前字符的编码
			while (*str != '\0')
			{
				if (offset >= 0)
				{
					data = data | ((*str - '0') << offset);
					offset--;
				}
				if (offset < 0)
				{
					fputc(data, fwrite);
					data = 0;
					offset = 7;
				}
				str++;
			}
			ch = fgetc(fread);
		}
		fputc(data, fwrite);
		WriteConfig(filename);
		fclose(fread);
		fclose(fwrite);
	}
	void UnCompress(const char* filename)
	{
		string fcp = filename;
		fcp += ".compress";
		FILE* fread = fopen(fcp.c_str(), "rb");
		if (fread == NULL)
		{
			cout << "打开文件失败..." << endl;
			return;
		}
		//打开文件成功
		//3、建立哈夫曼树
		CharInfo info[256];
		ReadConfig(filename, info);
		HuffmanTree<CharInfo> hft(info, 256, CharInfo());

		string fucp = filename;
		fucp += ".uncompress";
		FILE* fwrite = fopen(fucp.c_str(), "wb");

		HuffmanTreeNode<CharInfo>*root = hft.GetRoot();
		HuffmanTreeNode<CharInfo>*cur = root;//每次都要从根开始读，读到叶节点即可获取一个原字符
		long DataTotal = (root->_weight)._count;//原文件中的字符总数
		unsigned char ch = fgetc(fread);
		while (DataTotal)
		{
			int tmp = 1;
			int offset = 7;
			while (offset >= 0)
			{
				if (ch&(1 << offset))//检验位是否为0
				{
					cur = cur->_right;
					offset--;
				}
				else
				{
					cur = cur->_left;
					offset--;
				}
				if (cur->_left == NULL&&cur->_right == NULL)
				{
					unsigned char wch = cur->_weight._ch;
					fputc(wch, fwrite);
					cur = root;
					DataTotal--;
					//最后一个字符的编码在最后两个字节当中的情况
					if (!DataTotal)  
					{
						break;
					}
				}
			}
			ch = fgetc(fread);
		}
		fclose(fread);
		fclose(fwrite);
	}
protected:
	void WriteConfig(const char*filename)
	{
		string Config = filename;
		Config += "config";
		FILE* fwrite = fopen(Config.c_str(), "wb");
		if (fwrite == NULL)
		{
			cout << "打开文件失败" << endl;
			return;
		}
		//打开成功
		for (int i = 0; i < 256; i++)
		{
			if (_Info[i] ._count)
			{
				fputc(_Info[i]._ch, fwrite);
				fputc(',', fwrite);
				char count[100];
				//参数说明：1.要转换的值；2.结果存放区；3.进制
				_itoa(_Info[i]._count, count, 10);
				fputs(count, fwrite);
				fputc(',', fwrite);
				fputs(_Info[i]._code.c_str(), fwrite);
				fputc('\n', fwrite);
			}
		}
		fclose(fwrite);
	}
	void ReadConfig(const char*filename,CharInfo *info)
	{
		string Config = filename;
		Config += "config";
		FILE* fread = fopen(Config.c_str(), "rb");
		if (fread == NULL)
		{
			cout << "打开文件失败" << endl;
			return;
		}
		//打开成功
		char str[100];
		while (fgets(str, 100, fread))
		{
			char*pstr = str;
			unsigned char ch = (unsigned char)*pstr;//得到字符
			info[ch]._ch = ch;
			if (ch == '\n')
			{
				fgets(str, 100, fread);
				pstr=str;
				pstr++;
			}
			else
				pstr+=2;//跳过分隔符（逗号）
			//得到_count的字符串形式
			long count = 0;
			while (*pstr&&*pstr!=',')
			{
				count *= 10;
				count += *pstr - '0';
				pstr++;
			}
			info[ch]._count = count;//得到出现次数
			pstr++;
			string code(pstr);
			info[ch]._code = code;
		}
	}
	void GetHuffmanCodeOfChar(HuffmanTreeNode<CharInfo>*root, string& code)
	{
		if (root == NULL)
			return;
		if (root->_left == NULL&&root->_right == NULL)
		{
			unsigned char ch = root->_weight._ch;
			_Info[ch]._code = code;
			return;
		}
		GetHuffmanCodeOfChar(root->_left, code + '0');//左边编码为0
		GetHuffmanCodeOfChar(root->_right, code + '1');//右边编码为1
	}

private:
	CharInfo _Info[256];//结构体数组
};