using System;

namespace OutPut
{
    public class GeneOutPut
    {
        public static void Main()
        {
            
            int yInt = 2;
            double yDouble = 5.2;
            char yChar = 'y';

            GeneOutPut.GOutput(yInt);
            GeneOutPut.GOutput(yDouble);
            GeneOutPut.GOutput(yChar);
            Console.ReadKey();
        }

        
        public static void GOutput(int yInt)
        {
            Console.WriteLine("���ͣ�" + yInt);
        }
      
        public static void GOutput(double yDouble)
        {
            Console.WriteLine("˫���ȸ����ͣ�" + yDouble);
        }
       
        public static void GOutput(char yChar)
        {
            Console.WriteLine("�ַ������ݣ�" + yChar);
        }


    }
}