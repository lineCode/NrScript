/**
 * NrScript Source Code File saved as UTF-8.bom format 
 * 
 * note : 1. NrScript��������char�����ַ���(���֡�����)�����޶�ΪӢ�� 
 *        2. ���ض�ϵͳƽ̨��صĴ��룬�����platformĿ¼��
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 *        
 * !��Ҫ�ڴ�����ƽ̨��ص�ͷ�ļ���
 */

#include "NrScript/base.h"
#include "NrScript/ui.h"

/**
 * ͨ�ÿؼ�Ԥע��
 */
class NrWidgets {
public:
    /**
     * Ĭ�Ϲ��캯��
     */
    NrWidgets() {
        NrWidgetStringCreator<NrControl>(L"Control");
    }
};
static NrWidgets kCommonWidgetsRegister;