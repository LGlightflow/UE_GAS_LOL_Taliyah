




#include "UI/Widget/UIUserWidget.h"
//BP中调用
void UUIUserWidget::SetWidgetController(UObject* InWidgetController)
{

	WidgetController = InWidgetController;
	//触发时调用蓝图，蓝图中关联了WidgetController和血条蓝条，并进行设置
	//因为overlay中包含了血条和蓝条(血条蓝条是子类)，所以要这么设置
	WidgetControllerSet();
}

