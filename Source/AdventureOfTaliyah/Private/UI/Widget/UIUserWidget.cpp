




#include "UI/Widget/UIUserWidget.h"
//BP�е���
void UUIUserWidget::SetWidgetController(UObject* InWidgetController)
{

	WidgetController = InWidgetController;
	//����ʱ������ͼ����ͼ�й�����WidgetController��Ѫ������������������
	//��Ϊoverlay�а�����Ѫ��������(Ѫ������������)������Ҫ��ô����
	WidgetControllerSet();
}

