#include "fre_cal.h"


void fre_get(void)
{
	if		 ((frequency > 9750000 ) && (frequency <= 10250000))	{frequency = 10000000;}
	else if((frequency > 10250000) && (frequency <=  10750000 )){frequency = 10500000;}
	else if((frequency > 10750000) && (frequency <=  11250000 )){frequency = 11000000;}
	else if((frequency > 11250000) && (frequency <=  11750000 )){frequency = 11500000;}
	else if((frequency > 11750000) && (frequency <=  12250000 )){frequency = 12000000;}
	else if((frequency > 12250000) && (frequency <=  12750000 )){frequency = 12500000;}
	else if((frequency > 12750000) && (frequency <=  13250000 )){frequency = 13000000;}
	else if((frequency > 13250000) && (frequency <=  13750000 )){frequency = 13500000;}
	else if((frequency > 13750000) && (frequency <=  14250000 )){frequency = 14000000;}
	else if((frequency > 14250000) && (frequency <=  14750000 )){frequency = 14500000;}
	else if((frequency > 14750000) && (frequency <=  15250000 )){frequency = 15000000;}
	else if((frequency > 15250000) && (frequency <=  15750000 )){frequency = 15500000;}
	else if((frequency > 15750000) && (frequency <=  16250000 )){frequency = 16000000;}
	else if((frequency > 16250000) && (frequency <=  16750000 )){frequency = 16500000;}
	else if((frequency > 16750000) && (frequency <= 17250000  )){frequency = 17000000;}
	else if((frequency > 17250000) && (frequency <=  17750000 )){frequency = 17500000;}
	else if((frequency > 17750000) && (frequency <=  18250000 )){frequency = 18000000;}
	else if((frequency > 18250000) && (frequency <=  18750000 )){frequency = 18500000;}
	else if((frequency > 18750000) && (frequency <=  19250000 )){frequency = 19000000;}
	else if((frequency > 19250000) && (frequency <=  19750000 )){frequency = 19500000;}
	else if((frequency > 19750000) && (frequency <=  20250000 )){frequency = 20000000;}
	else if((frequency > 20250000) && (frequency <=  20750000 )){frequency = 20500000;}
	else if((frequency > 20750000) && (frequency <=  21250000 )){frequency = 21000000;}
	else if((frequency > 21250000) && (frequency <=  21750000 )){frequency = 21500000;}
	else if((frequency > 21750000) && (frequency <=  22250000 )){frequency = 22000000;}
	else if((frequency > 22250000) && (frequency <=  22750000 )){frequency = 22500000;}
	else if((frequency > 22750000) && (frequency <=  23250000 )){frequency = 23000000;}
	else if((frequency > 23250000) && (frequency <=  23750000 )){frequency = 23500000;}
	else if((frequency > 23750000) && (frequency <=  24250000 )){frequency = 24000000;}
	else if((frequency > 24250000) && (frequency <=  24750000 )){frequency = 24500000;}
	else if((frequency > 24750000) && (frequency <=  25250000 )){frequency = 25000000;}
	else if((frequency > 25250000) && (frequency <=  25750000 )){frequency = 25500000;}
	else if((frequency > 25750000) && (frequency <=  26250000 )){frequency = 26000000;}
	else if((frequency > 26250000) && (frequency <=  26750000 )){frequency = 26500000;}
	else if((frequency > 26750000) && (frequency <=  27250000 )){frequency = 27000000;}
	else if((frequency > 27250000) && (frequency <=  27750000 )){frequency = 27500000;}
	else if((frequency > 27750000) && (frequency <=  28250000 )){frequency = 28000000;}
	else if((frequency > 28250000) && (frequency <=  28750000 )){frequency = 28500000;}
	else if((frequency > 28750000) && (frequency <=  29250000 )){frequency = 29000000;}
	else if((frequency > 29250000) && (frequency <=  29750000 )){frequency = 29500000;}
	else if((frequency > 29750000) && (frequency <=  30250000 )){frequency = 30000000;}

}

//void AM_Fre(void)
//{
//	


//}