using System;
using System.Runtime.InteropServices;
namespace Delegate {  
        // �ܵ����±�����
        public class Heater {  
           private int temperature;  
           public string type = "�ܵ��¶�";
           public string area = "���ֻ���";  
           //����ί��  
           public delegate void HeatEventHandler(Object sender, HeatEventArgs e);  
           public event HeatEventHandler Heat; //�����¼�  
      
           // ����HeatEventArgs�࣬���ݸ�Observer������Ȥ����Ϣ  
           public class HeatEventArgs : EventArgs {  
               public readonly int temperature;  
               public HeatEventArgs(int temperature) {  
                  this.temperature = temperature;  
               }  
           }  
      
           // ���Թ��̳��� Heater ������д���Ա�̳���ܾ�������������ļ���  
           protected virtual void OnHeat(HeatEventArgs e) {  
               if (Heat != null) { // ����ж���ע��  
                  Heat(this, e);  // ��������ע�����ķ���  
               }  
           }  
             
           // ���¡�  
           public void OverHeat() {
               Console.WriteLine("�����뾯���¶�ֵ");
               int a = Convert.ToInt32(Console.ReadLine());//���뾯���¶�ֵ
               for (int i = 0; i <= 100; i++) {       
                  temperature = i;
                  Console.WriteLine("�����¶�{0}", i);
                  Console.WriteLine();
                  if (temperature > a) {  
                      //����HeatEventArgs ����  
                      HeatEventArgs e = new HeatEventArgs(temperature);
                      OnHeat(e);  // ���� Heat����  
                  }  
               }
               Console.WriteLine("GANE OVER");
           }  
        }  
      
        // ������  
        public class Alarm {
            [DllImport("kernel32.dll")]
            private static extern int Beep(int dwFreq, int dwDuration); 
           public void MakeAlert(Object sender, Heater.HeatEventArgs e) {  
               Heater heater = (Heater)sender;
               //���� sender �еĹ����ֶ�  
               Console.WriteLine("{0} - {1}: ", heater.area, heater.type);
               int a = 0X7FF;  //����Ƶ��(Hz)
               int b = 1000;  //����ʱ��(����)
               Beep(a, b); 
               Console.WriteLine("�ܵ��Ѿ� {0} ���ˣ�", e.temperature);  
               Console.WriteLine();  
           }  
        }  
      
        // ��ʾ��  
        public class Display {  
           public static void ShowMsg(Object sender, Heater.HeatEventArgs e) {   //��̬����  
               Heater heater = (Heater)sender;  
               Console.WriteLine("{0} - {1}: ", heater.area, heater.type);  
               Console.WriteLine("�ܵ������ˣ���ǰ�¶ȣ�{0}�ȡ�", e.temperature);  
               Console.WriteLine();  
           }  
        }  
      
        class Program {  
           static void Main() {  
               Heater heater = new Heater();  
               Alarm alarm = new Alarm();  
      
               heater.Heat += alarm.MakeAlert;   //ע�᷽��  
               heater.Heat += (new Alarm()).MakeAlert;      //����������ע�᷽��  
               heater.Heat += new Heater.HeatEventHandler(alarm.MakeAlert);    //Ҳ������ôע��  
               heater.Heat += Display.ShowMsg;      //ע�ᾲ̬����  
               heater.OverHeat();   //���Զ�����ע�������ķ���  
           }  
        }  
    }  
      
    