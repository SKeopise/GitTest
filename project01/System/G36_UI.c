#include <G36_UI.h>


static unsigned char current_index = _main_ui;		//当前页面索引缓存
static unsigned char last_index = _main_ui;			//上个页面索引缓存
static void(*current_operation_real)(unsigned char,unsigned char);		//运行函数指针




UI_table menu_table[] = 
{
	
	{_main_ui,_main_ui,_main_ui,_menu_main_1,_end_,Main_UI_show}, 		//进入界面
	
	{_menu_main_1,_menu_2nd_1,_menu_3rd_1,_menu_main_2,_main_ui,Menu_UI1_show1},
	{_menu_2nd_1,_menu_3rd_1,_menu_main_1,_menu_2nd_2,_main_ui,Menu_UI1_show2},
	{_menu_3rd_1,_menu_main_1,_menu_2nd_1,_menu_3rd_2,_main_ui,Menu_UI1_show3},
	
	{_menu_main_2,_menu_2nd_2,_menu_3rd_2,_menu_main_2,_menu_main_1,Menu_UI2_show1},
	{_menu_2nd_2,_menu_3rd_2,_menu_main_2,_menu_2nd_3,_menu_2nd_1,Menu_UI2_show2},
	{_menu_3rd_2,_menu_main_2,_menu_2nd_2,_menu_3rd_2,_menu_3rd_1,Menu_UI2_show3},
		
	{_end_,_main_ui,_main_ui,_main_ui,_main_ui,Menu_end},	
		
};

void G36_UI_Driver()
{
	unsigned char key_val = Key_Driver();
	
	if(key_val != 0)
	{
		last_index = current_index;
		switch(key_val)
		{
			case 1:	current_index = menu_table[current_index].down;	break;
			case 2: current_index = menu_table[current_index].enter;    break;
			default:break;
		}
		OLED_Clear();
	}
	current_operation_real = menu_table[current_index].current_operation;
	(*current_operation_real)(current_index,key_val);

}



void Main_UI_show(unsigned char index,unsigned char next)
{
	OLED_ShowNum(1,1,index,2);
	OLED_ShowNum(1,4,next,2);
}

void Menu_UI1_show1(unsigned char index,unsigned char next)
{
	OLED_ShowNum(2,1,index,2);
	OLED_ShowNum(2,4,next,2);
}

void Menu_UI1_show2(unsigned char index,unsigned char next)
{
	OLED_ShowNum(2,2,index,2);
	OLED_ShowNum(2,5,next,2);
}

void Menu_UI1_show3(unsigned char index,unsigned char next)
{
	OLED_ShowNum(2,3,index,2);
	OLED_ShowNum(2,6,next,2);
}

void Menu_UI2_show1(unsigned char index,unsigned char next)
{
	OLED_ShowNum(3,1,index,2);
	OLED_ShowNum(3,4,next,2);
}

void Menu_UI2_show2(unsigned char index,unsigned char next)
{
	OLED_ShowNum(3,2,index,2);
	OLED_ShowNum(3,5,next,2);
}

void Menu_UI2_show3(unsigned char index,unsigned char next)
{
	OLED_ShowNum(3,3,index,2);
	OLED_ShowNum(3,6,next,2);
}

void Menu_end(unsigned char index,unsigned char next)
{
	OLED_Clear();
}
