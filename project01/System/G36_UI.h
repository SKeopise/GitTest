#ifndef _G36_UI_H_
#define _G36_UI_H_

#include <Key.h>
#include <OLED.h>

typedef struct
{
	unsigned char current; 	//当前页面索引值
	unsigned char down;  	//向下索引号
	unsigned char up; 		//向上索引号
	unsigned char enter;	//下一级菜单索引号
	unsigned char back;		//上一级菜单索引
	void(*current_operation)(unsigned char,unsigned char);	  //实际函数指针
}UI_table;

enum
{
	_main_ui = 0,		//主界面
	
	_menu_main_1,       //一级菜单
	_menu_2nd_1,
	_menu_3rd_1,
	
	_menu_main_2,		//二级菜单	
	_menu_2nd_2,
	_menu_3rd_2,
	
	_menu_main_3,		//三级菜单
	_menu_2nd_3,
	_menu_3rd_3,
	
	_end_,				//结束
};






void G36_UI_Driver();


void Main_UI_show(unsigned char index,unsigned char);
void Menu_UI1_show1(unsigned char index,unsigned char next);
void Menu_UI1_show2(unsigned char index,unsigned char next);
void Menu_UI1_show3(unsigned char index,unsigned char next);

void Menu_UI2_show1(unsigned char index,unsigned char next);
void Menu_UI2_show2(unsigned char index,unsigned char next);
void Menu_UI2_show3(unsigned char index,unsigned char next);
void Menu_end(unsigned char index,unsigned char next);







#endif
