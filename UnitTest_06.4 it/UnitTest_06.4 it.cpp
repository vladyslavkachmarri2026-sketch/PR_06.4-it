#include "pch.h"
#include "CppUnitTest.h"
#include "../PR_06.4 it.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest64
{
	TEST_CLASS(UnitTest64)
	{
	public:

		// 1. Тест пошуку індексу елемента з найбільшим модулем
		TEST_METHOD(TestIndexMaxAbs)
		{
			double arr[5] = { -2.5, 3.1, -9.8, 4.2, 0.5 };
			// Найбільший за модулем |-9.8| = 9.8 (індекс 2)
			int expected = 2;
			int actual = IndexMaxAbs(arr, 5);

			Assert::AreEqual(expected, actual);
		}

		// 2. Тест суми елементів після першого додатного
		TEST_METHOD(TestSumAfter)
		{
			double arr[5] = { -3.0, 2.5, 1.0, -4.0, 5.0 };
			// Перший додатний — 2.5 (індекс 1)
			// Сума елементів після нього: 1.0 + (-4.0) + 5.0 = 2.0
			int ifirst = IndexFirstPositive(arr, 5);
			Assert::AreEqual(1, ifirst);

			double expectedSum = 2.0;
			double actualSum = SumAfter(arr, 5, ifirst);

			// Для дійсних чисел використовуємо допуск точності (eps = 0.0001)
			Assert::AreEqual(expectedSum, actualSum, 0.0001);
		}

		// 3. Тест стабільної перестановки
		TEST_METHOD(TestMoveByIntPart)
		{
			double arr[5] = { -4.27, 2.8, -1.1, 5.5, 0.3 };
			// floor(-4.27) = -5, floor(2.8) = 2, floor(-1.1) = -2, floor(5.5) = 5, floor(0.3) = 0
			// Інтервал [A; B] = [-3; 2]
			// Елементи у діапазоні: 2.8 (ціла частина 2), -1.1 (ціла частина -2), 0.3 (ціла частина 0)
			// Усі інші: -4.27 (ціла частина -5), 5.5 (ціла частина 5)

			double expected[5] = { 2.8, -1.1, 0.3, -4.27, 5.5 };

			MoveByIntPart(arr, 5, -3.0, 2.0);

			for (int i = 0; i < 5; i++)
			{
				Assert::AreEqual(expected[i], arr[i], 0.0001);
			}
		}
	};
}