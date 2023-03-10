#ifndef _EXYNOS_SETUP_HEAD_H
#define _EXYNOS_SETUP__HEAD_H

/*********************************************************************
 *宏的作用:
 *SET_GPIO_MODE ()  设置GPIO的工作模式
 *SET_GPIO_LEVEL()  设置GPIO的电平状态
 *GET_GPIO_LEVEL()  获取GPIO的电平状态
 *
 *作者:
 *草根老师
 *********************************************************************/

#define INPUT       0x0
#define OUTPUT      0x1

#define SET_GPIO_MODE(reg,pin,mode) do{\
		reg &= ~( 0xf  << (pin * 4));\
		reg |=  ( mode << (pin * 4));\
}while(0)


#define HIGH   1
#define LOW    0

#define SET_GPIO_LEVEL(reg,pin,level) do{\
		reg &= ~( 0x1   << pin );\
		reg |=  ( level << pin);\
}while(0)

#define GET_GPIO_LEVEL(reg,pin) ({\
	int level;\
	if(reg & (1 << pin))\
		level = HIGH;\
	else\
		level = LOW;\
	level;\
})

/***********************************CMU_CPU*************************/

/* CLK_SRC_CPU */
#define MUX_MPLL_USER_SEL_C_ FINPLL     0x0
#define MUX_MPLL_USER_SEL_C_FOUTMPLL    0x1
#define MUX_HPM_SEL_MOUTAPLL			0x0
#define MUX_HPM_SEL_SCLKMPLL			0x1
#define MUX_CORE_SEL_MOUTAPLL			0x0
#define MUX_CORE_SEL_SCLKMPLL			0x1
#define MUX_MPLL_SEL_FILPLL		   		0x0
#define MUX_MPLL_SEL_MOUTMPLLFOUT		0x1
#define MUX_APLL_SEL_FILPLL		    	0x0
#define MUX_APLL_SEL_MOUTMPLLFOUT		0x1
#define CLK_SRC_CPU_VAL		(( MUX_MPLL_USER_SEL_C_FOUTMPLL << 24)\
					| (MUX_HPM_SEL_MOUTAPLL << 20) \
					| (MUX_CORE_SEL_MOUTAPLL << 16) \
					| (MUX_APLL_SEL_MOUTMPLLFOUT << 0))


/* CLK_DIV_CPU0 */
#define APLL_RATIO		    0x0
#define CORE_RATIO		    0x0
#define CORE2_RATIO         0x0
#define COREM0_RATIO		0x3
#define COREM1_RATIO		0x7
#define PERIPH_RATIO		0x3
#define ATB_RATIO		    0x4
#define PCLK_DBG_RATIO		0x0

#define CLK_DIV_CPU0_VAL	((CORE2_RATIO << 28)\
                | (APLL_RATIO << 24) \
				| (PCLK_DBG_RATIO << 20) \
				| (ATB_RATIO << 16) \
				| (PERIPH_RATIO << 12) \
				| (COREM1_RATIO << 8) \
				| (COREM0_RATIO << 4) \
				| (CORE_RATIO << 0))


/* CLK_DIV_CPU1 */
#define CORES_RATIO     0x4
#define HPM_RATIO		0x3
#define COPY_RATIO		0x0
#define CLK_DIV_CPU1_VAL	((CORES_RATIO << 8 )\
				|(HPM_RATIO << 4) | (COPY_RATIO))


/* Required period to generate a stable clock output */
/* PLL_LOCK_TIME */
#define APLL_LOCKTIME   (APLL_PDIV * 270)

/*PLL Values*/
#define DISABLE			0
#define ENABLE			1
#define SET_PLL(mdiv, pdiv, sdiv)	((ENABLE << 31)\
					| (mdiv << 16) \
					| (pdiv << 8) \
					| (sdiv << 0))

/* APLL_CON0 */
#define APLL_PDIV		    3
#define APLL_MDIV		    125
#define APLL_SDIV		    0
#define APLL_CON0_VAL		SET_PLL(APLL_MDIV, APLL_PDIV, APLL_SDIV)

/* APLL_CON1 */
#define APLL_AFC_ENB		 0x1
#define APLL_AFC		     0xC
#define APLL_CON1_VAL		((APLL_AFC_ENB << 31) | (APLL_AFC << 0))


/***********************************CMU_DMC*************************/

/* CLK_SRC_DMC */
#define MUX_G2D_ACP_SEL_MOUTG2D_ACP_0 0x0
#define MUX_G2D_ACP_SEL_MOUTG2D_ACP_1 0x1
#define MUX_G2D_ACP_1_SEL_SCLKEPLL  0x0
#define MUX_G2D_ACP_1_SEL_SCLKVPLL  0x1
#define MUX_G2D_ACP_0_SEL_SCLKMPLL  0x0
#define MUX_G2D_ACP_0_SEL_SCLKAPLL  0x1
#define MUX_PWI_SEL_XXTI	 	    0x0
#define MUX_PWI_SEL_XUSBXTI	  	    0x1
#define MUX_PWI_SEL_SCLK_HDMI24M	0x2
#define MUX_PWI_SEL_SCLK_USBPHY0	0x3
#define MUX_PWI_SEL_SCLK_USBPHY1	0x4
#define MUX_PWI_SEL_SCLK_HDMIPHY	0x5
#define MUX_PWI_SEL_SCLKMPLL		0x6
#define MUX_PWI_SEL_SCLKEPLL		0x7
#define MUX_PWI_SEL_SCLKVPLL		0x8
#define MUX_DPHY_SEL_SCLKMPLL		0x0
#define MUX_DPHY_SEL_SCLKAPLL		0x1
#define MUX_MPLL_SEL_FINPLL		    0x0
#define MUX_MPLL_SEL_MOUTMPLLFOUT   0x1
#define MUX_DMC_BUS_SEL_SCLKMPLL	0x0
#define MUX_DMC_BUS_SEL_SCLKAPLL	0x1
#define MUX_C2C_SEL_SCLKSCLKMPLL    0x0
#define MUX_C2C_SEL_SCLKAPLL        0x1
#define CLK_SRC_DMC_VAL			((MUX_G2D_ACP_SEL_MOUTG2D_ACP_0 << 28)\
					| (MUX_G2D_ACP_0_SEL_SCLKMPLL << 20)\
					| (MUX_PWI_SEL_XUSBXTI << 16) \
					| (MUX_MPLL_SEL_MOUTMPLLFOUT << 12)\
					| (MUX_DPHY_SEL_SCLKMPLL << 8) \
					| (MUX_DMC_BUS_SEL_SCLKMPLL << 4)\
					| (MUX_C2C_SEL_SCLKSCLKMPLL << 0))




/* CLK_DIV_DMC0 */
#define DMCP_RATIO			0x1
#define DMCD_RATIO			0x1
#define DMC_RATIO			0x1
#define DPHY_RATIO			0x1
#define ACP_PCLK_RATIO		0x1
#define ACP_RATIO			0x3
#define CLK_DIV_DMC0_VAL	((DMCP_RATIO << 20) \
				| (DMCD_RATIO << 16) \
				| (DMC_RATIO << 12) \
				| (DPHY_RATIO << 8) \
				| (ACP_PCLK_RATIO << 4)	\
				| (ACP_RATIO << 0))


/* CLK_DIV_DMC1 */
#define DPM_RATIO			0x0
#define DVSEM_RATIO			0x0
#define C2C_ACLK_RATIO      0x0
#define PWI_RATIO			0x1
#define C2C_RATIO           0x0
#define G2D_ACP_RATIO  		0x0
#define CLK_DIV_DMC1_VAL	((DPM_RATIO << 24) \
				| (DVSEM_RATIO << 16) \
				| (C2C_ACLK_RATIO << 12)\
				| (PWI_RATIO << 8)\
				| (C2C_RATIO << 4)\
				| (G2D_ACP_RATIO))


/* Required period to generate a stable clock output */
/* PLL_LOCK_TIME */
#define MPLL_LOCKTIME   (MPLL_PDIV * 270)

/*PLL Values*/
#define DISABLE			0
#define ENABLE			1
#define SET_PLL(mdiv, pdiv, sdiv)	((ENABLE << 31)\
					| (mdiv << 16) \
					| (pdiv << 8) \
					| (sdiv << 0))


/* MPLL_CON0 */
#define MPLL_PDIV			0x3
#define MPLL_MDIV			100
#define MPLL_SDIV			0x0
#define MPLL_CON0_VAL		SET_PLL(MPLL_MDIV, MPLL_PDIV, MPLL_SDIV)

/* MPLL_CON1 */
#define MPLL_AFC_ENB		0x0
#define MPLL_AFC		    0x1C
#define MPLL_CON1_VAL		((MPLL_AFC_ENB << 31) | (MPLL_AFC << 0))



/***********************************CMU_TOP*************************/

/* CLK_SRC_TOP0 */
#define MUX_ONENAND_SEL_ACLK_133		0x0
#define MUX_ONENAND_SEL_ACLK_160		0x1
#define MUX_ACLK_133_SEL_SCLKMPLL		0x0
#define MUX_ACLK_133_SEL_SCLKAPLL		0x1
#define MUX_ACLK_160_SEL_SCLKMPLL		0x0
#define MUX_ACLK_160_SEL_SCLKAPLL		0x1
#define MUX_ACLK_100_SEL_SCLKMPLL		0x0
#define MUX_ACLK_100_SEL_SCLKAPLL		0x1
#define MUX_ACLK_200_SEL_SCLKMPLL		0x0
#define MUX_ACLK_200_SEL_SCLKAPLL		0x1
#define MUX_VPLL_SEL_FINPLL				0x0
#define MUX_VPLL_SEL_FOUTVPLL			0x1
#define MUX_EPLL_SEL_FINPLL				0x0
#define MUX_EPLL_SEL_FOUTEPLL			0x1
#define MUX_ONENAND_1_SEL_MOUTONENAND	0x0
#define MUX_ONENAND_1_SEL_SCLKVPLL		0x1
#define CLK_SRC_TOP0_VAL		((MUX_ONENAND_SEL_ACLK_133 << 28) \
					| (MUX_ACLK_133_SEL_SCLKMPLL << 24) \
					| (MUX_ACLK_160_SEL_SCLKMPLL << 20) \
					| (MUX_ACLK_100_SEL_SCLKMPLL << 16) \
					| (MUX_ACLK_200_SEL_SCLKMPLL << 12) \
					| (MUX_VPLL_SEL_FINPLL << 8) \
					| (MUX_EPLL_SEL_FINPLL << 4)\
					| (MUX_ONENAND_1_SEL_MOUTONENAND << 0))

/* CLK_SRC_TOP1 */
#define MUX_ACLK_400_MCUISP_SUB_SEL_FINPLL   				 0x0
#define MUX_ACLK_400_MCUISP_SUB_SEL_DIVOUT_ACLK_400_MCUISP   0x1
#define MUX_ACLK_200_SUB_SEL_FINPLL          		 	     0x0
#define MUX_ACLK_200_SUB_SEL_DIVOUT_ACLK_200         		 0x1
#define MUX_ACLK_266_GPS_SUB_SEL_FINPLL 			 		 0x0
#define MUX_ACLK_266_GPS_SUB_SEL_DIVOUT_ACLK_266_GPS  		 0x1
#define MUX_MPLL_USER_SEL_T_FINPLL                 	 		 0x0
#define MUX_MPLL_USER_SEL_T_SCLKMPLLL                		 0x1
#define MUX_ACLK_400_MCUISP_SEL_SCLKMPLL_USER_T      		 0x0
#define MUX_ACLK_400_MCUISP_SEL_SCLKAPLL      		 		 0x1
#define MUX_ACLK_266_GPS_SEL_SCLKMPLL_USER_T   		 		 0x0
#define MUX_ACLK_266_GPS_SEL_SCLKAPLL   	  		  		 0x1
#define CLK_SRC_TOP1_VAL		((MUX_ACLK_400_MCUISP_SUB_SEL_DIVOUT_ACLK_400_MCUISP << 24)\
								 |(MUX_ACLK_200_SUB_SEL_DIVOUT_ACLK_200 << 20)\
								 |(MUX_ACLK_266_GPS_SUB_SEL_DIVOUT_ACLK_266_GPS << 16)\
								 |(MUX_MPLL_USER_SEL_T_SCLKMPLLL << 12)\
								 |(MUX_ACLK_400_MCUISP_SEL_SCLKMPLL_USER_T << 8)\
								 |(MUX_ACLK_266_GPS_SEL_SCLKMPLL_USER_T << 4))

/* CLK_DIV_TOP */
#define ACLK_400_MCUISP_RATIO   0x1
#define ACLK_266_GPS_RATIO  	0x2
#define ONENAND_RATIO			0x0
#define ACLK_133_RATIO			0x5
#define ACLK_160_RATIO			0x4
#define ACLK_100_RATIO			0x7
#define ACLK_200_RATIO			0x3
#define CLK_DIV_TOP_VAL		((ACLK_400_MCUISP_RATIO << 24)\
				| (ACLK_266_GPS_RATIO << 20)\
				| (ONENAND_RATIO << 16)	\
				| (ACLK_133_RATIO << 12)\
				| (ACLK_160_RATIO << 8)	\
				| (ACLK_100_RATIO << 4)	\
				| (ACLK_200_RATIO << 0))


/***********************************CMU_LEFTBUS*************************/
/* CLK_SRC_LEFTBUS */
#define MUX_MPLL_USER_SEL_L_FINPLL		0x0
#define MUX_MPLL_USER_SEL_L_FOUTMPLL	0x1
#define MUX_GDL_SEL_SCLKMPLL			0x0
#define MUX_GDL_SEL_SCLKAPLL			0x1
#define CLK_SRC_LEFTBUS_VAL	  ((MUX_MPLL_USER_SEL_L_FOUTMPLL << 4) | (MUX_GDL_SEL_SCLKMPLL << 0))

/* CLK_DIV_LEFTBUS */
#define GPL_RATIO		0x1
#define GDL_RATIO		0x3
#define CLK_DIV_LEFTBUS_VAL	((GPL_RATIO << 4) | (GDL_RATIO))


/***********************************CMU_RIGHTBUS*************************/
/* CLK_SRC_RIGHTBUS */
#define MUX_MPLL_USER_SEL_R_FINPLL		0x0
#define MUX_MPLL_USER_SEL_R_FOUTMPLL	0x1
#define MUX_GDR_SEL_SCLKMPLL			0x0
#define MUX_GDR_SEL_SCLKAPLL			0x1
#define CLK_SRC_RIGHTBUS_VAL	(MUX_MPLL_USER_SEL_R_FOUTMPLL << 4) | (MUX_GDR_SEL_SCLKMPLL)

/* CLK_DIV_RIGHTBUS */
#define GPR_RATIO		0x1
#define GDR_RATIO		0x3
#define CLK_DIV_RIGHTBUS_VAL	((GPR_RATIO << 4) | (GDR_RATIO))


/***********************************CMU_UART*************************/

/* CLK_SRC_PERIL0 */
#define UART_SEL_XXTI		0
#define UART_SEL_XUSBXTI	1
#define UART_SEL_SCLK_HDMI24M	2
#define UART_SEL_SCLK_USBPHY0	3
#define UART_SEL_SCLK_USBPHY1	4
#define UART_SEL_SCLK_HDMIPHY	5
#define UART_SEL_SCLKMPLL	6
#define UART_SEL_SCLKEPLL	7
#define UART_SEL_SCLKVPLL	8

#define UART0_SEL		UART_SEL_SCLKMPLL
#define UART1_SEL		UART_SEL_SCLKMPLL
#define UART2_SEL		UART_SEL_SCLKMPLL
#define UART3_SEL		UART_SEL_SCLKMPLL
#define UART4_SEL		UART_SEL_SCLKMPLL
#define CLK_SRC_PERIL0_VAL	((UART4_SEL << 16) \
				| (UART3_SEL << 12) \
				| (UART2_SEL << 8) \
				| (UART1_SEL << 4) \
				| (UART0_SEL << 0))

/* SCLK_UART[0-4] = MOUTUART[0-4]/(UART[0-4]_RATIO + 1) */
/* CLK_DIV_PERIL0 */
#define UART0_RATIO		7
#define UART1_RATIO		7
#define UART2_RATIO		7
#define UART3_RATIO		7
#define UART4_RATIO		7
#define CLK_DIV_PERIL0_VAL	((UART4_RATIO << 16) \
				| (UART3_RATIO << 12) \
				| (UART2_RATIO << 8) \
				| (UART1_RATIO << 4) \
				| (UART0_RATIO << 0))


/*********************************UART 配置***************************/

/* ULCON: UART Line Control Value 8N1 */
#define WORD_LEN_5_BIT				0x00
#define WORD_LEN_6_BIT				0x01
#define WORD_LEN_7_BIT				0x02
#define WORD_LEN_8_BIT				0x03

#define STOP_BIT_1					0x00
#define STOP_BIT_2					0x01

#define NO_PARITY					0x00
#define ODD_PARITY					0x4
#define EVEN_PARITY					0x5
#define FORCED_PARITY_CHECK_AS_1	0x6
#define FORCED_PARITY_CHECK_AS_0	0x7

#define INFRAMODE_NORMAL			0x00
#define INFRAMODE_INFRARED			0x01

#define ULCON_VAL		((INFRAMODE_NORMAL << 6) \
				| (NO_PARITY << 3) \
				| (STOP_BIT_1 << 2) \
				| (WORD_LEN_8_BIT << 0))


/*
 * UCON: UART Control Value
 * Transmit mode : Interrupt request/polling
 * Receive mode : Interrupt request/polling
 */
#define TX_MODE_IRQ_OR_POLL				0X01
#define RX_MODE_IRQ_OR_POLL				0X01

#define UCON_VAL  ((TX_MODE_IRQ_OR_POLL << 2)|(RX_MODE_IRQ_OR_POLL << 0))

/*
 * Baud Rate Division Value
 * 115200 BAUD:
 * DIV_VAL    = (SCLK_UART/(115200 * 16)) - 1
 * 			  = ((100 MHz)/(115200 * 16)) - 1
 *  		  = 53.2
 *UBRDIV      = 20 (integer part of DIV_VAL)
 *
 *UFRACVAL/16 = 0.25
 *UFRACVAL    = 0.25 * 16 = 4
 */
#define UBRDIV_VAL		    53
#define UFRACVAL_VAL		4

#endif
