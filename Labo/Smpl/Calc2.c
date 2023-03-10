/*
	Calc2.exe [/R <Radix>] [/E <Effect>] /EM <Number>

	Calc2.exe [/R <Radix>] [/S] [/E <Effect>] [/-R] /P <Number> <Exponent>

	Calc2.exe [/R <Radix>] [/B <Basement>] [/S] [/E <Effect>] [/-R] /R <Number> <Exponent>

	Calc2.exe [/R <Radix>] [/B <Basement>] [/-R] <Number> <Operator> <Number> <Effect>

	Calc2.exe [/R <Radix>] [/B <Basement>] [/S] [/E <Effect>] [/-R] <Number> <Operator> <Number>

	Calc2.exe [/R <Radix>] [/-R] <Number> <Effect>

	Calc2.exe [/R <Radix>] [/S] [/E <Effect>] [/-R] <Number>

		Radix    ...     2 〜 36
		Basement ... -IMAX 〜 IMAX
		Effect   ...     0 〜 IMAX
		Exponent ...     0 〜 4294967295

		Number ... 実数 | 実数の指数表記

			大きな指数を指定することによってメモリ不足や処理に時間が掛かる状況を引き起こせることに注意！

		Operator ... + - * /

	----
	例

	Calc2 /S 123.456   ==>   1.23456E+02

	Calc2 /E 10 /EM 123.456   ==>   123.4560000

	- - -

	Calc2 /B 20 2 / 3 21   ==>   6.66666666666666666660E-01

	Calc2 /B 20 2 / 3 20   ==>   6.6666666666666666666E-01

	Calc2 /B 20 2 / 3 19   ==>   6.666666666666666667E-01

	- - -

	Calc2 /B 19 2 / 3 20   ==>   6.6666666666666666660E-01

	Calc2 /B 20 2 / 3 20   ==>   6.6666666666666666666E-01

	Calc2 /B 21 2 / 3 20   ==>   6.6666666666666666667E-01
*/

#include "C:\Factory\Common\all.h"
#include "C:\Factory\Common\Options\Calc2.h"

int main(int argc, char **argv)
{
readArgs:
	if (argIs("/X"))
	{
		calcRadix = toValue(nextArg()); // 2 〜 36, 範囲外 -> calc()でerror();
		goto readArgs;
	}
	if (argIs("/B"))
	{
		calcBasement = atoi(nextArg()); // -IMAX 〜 IMAX, 範囲外 -> calc()でerror();
		goto readArgs;
	}
	if (argIs("/S"))
	{
		calcScient = 1;
		goto readArgs;
	}
	if (argIs("/E"))
	{
		calcEffect = toValue(nextArg()); // 0 == 無効, 1 〜 IMAX, 範囲外 -> calc()でerror();
		goto readArgs;
	}
	if (argIs("/-R"))
	{
		calcRndOff = 0;
		goto readArgs;
	}

	/*
		Calc2 /e 10 /em 123.456 とか
	*/
	if (argIs("/EM"))
	{
		calcOperand_t *co = calcFromString(nextArg());
		char *ret;

		ret = calcGetSmplString_EM(co, calcEffect);
		calcRelease(co);
		cout("%s\n", ret);
		memFree(ret);
		return;
	}

	/*
		べき乗
	*/
	if (argIs("/P"))
	{
		calcOperand_t *co = calcFromString(getArg(0));
		uint exponent = toValue(getArg(1));

		cout("%s\n", c_calcGetString_x(calcPower(co, exponent)));

		calcRelease(co);
		return;
	}

	/*
		べき根
	*/
	if (argIs("/R"))
	{
		calcOperand_t *co = calcFromString(getArg(0));
		uint exponent = toValue(getArg(1));

		cout("%s\n", c_calcGetString_x(calcRoot(co, exponent)));

		calcRelease(co);
		return;
	}

	if (hasArgs(4))
	{
		calcScient = 1;
		calcEffect = toValue(getArg(3));
		cout("%s\n", c_calc(getArg(0), getArg(1)[0], getArg(2)));
		return;
	}
	if (hasArgs(3))
	{
		cout("%s\n", c_calc(getArg(0), getArg(1)[0], getArg(2)));
		return;
	}
	if (hasArgs(2))
	{
		calcScient = 1;
		calcEffect = toValue(getArg(1));
		cout("%s\n", c_calcGetString_x(calcFromString(getArg(0))));
		return;
	}
	if (hasArgs(1))
	{
		cout("%s\n", c_calcGetString_x(calcFromString(getArg(0))));
		return;
	}
	error();
}
