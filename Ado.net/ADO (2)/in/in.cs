
using System;
#if STRONG
[assembly:System.Reflection.AssemblyVersion("0.0.0.0")]
[assembly:System.Reflection.AssemblyKeyFile("orgKey.snk")]
#endif
namespace Input
{

    public class GeneInput
    {
        public static int GeneInputInt()
        {
            while (true)
            {
                try
                {
                    Console.WriteLine("������һ��int���͵�ֵ");
                    int yInt = int.Parse(Console.ReadLine());
                    return yInt;
                }

                catch (ArgumentNullException e)
                {
                    Console.WriteLine("���������Ϊ��, ���������룡");
                }
                catch (FormatException e)
                {
                    Console.WriteLine("������Ĳ�������, ���������룡");
                }

            }

        }
        public static Double GeneInputDouble()
        {
            while (true)
            {
                try
                {
                    Console.WriteLine("������˫���������͵�ֵ");
                    double yDouble = Double.Parse(Console.ReadLine());
                    return yDouble;
                }
                catch (ArgumentNullException e)
                {
                    Console.WriteLine("���������Ϊ��, ���������룡");
                }
                catch (FormatException e)
                {
                    Console.WriteLine("������Ĳ���˫����, ���������룡");
                }
            }
        }
        public static char GeneInputChar()
        {
            while (true)
            {
                try
                {
                    Console.WriteLine("������һ���ַ���ֵ");
                    char yChar = char.Parse(Console.ReadLine());
                    return yChar;
                }
                catch (ArgumentNullException e)
                {
                    Console.WriteLine("���������Ϊ��, ���������룡");
                }
                catch (FormatException e)
                {
                    Console.WriteLine("������Ĳ����ַ�, ���������룡");
                }

            }

        }

    }
}