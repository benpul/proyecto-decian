#include <16F877A.h>
#device adc=8
#fuses XT, NOWDT, PUT, NOPROTECT, NODEBUG, NOBROWNOUT, NOLVP, NOCPD, NOWRT,
#use delay(clock=4000000)
float volta,volti,voltd,disa,disi,disd;
long  adelante,izq,der;
float decimal= 5/256; //asi con los comentarios//
#include <math.h>
void giro_180(){
	setup_timer_2(T2_DIV_BY_1,10000,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
	setup_ccp1(CCP_PWM);
    setup_ccp2(CCP_PWM);
    set_pwm1_duty(70);
	set_pwm2_duty(30);
	delay_ms(500);
}

void giro_der90(){
	
    setup_timer_2(T2_DIV_BY_1,1000,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
	setup_ccp1(CCP_PWM);
    setup_ccp2(CCP_PWM);
    set_pwm1_duty(70);
	set_pwm2_duty(30);
	delay_ms(250);
}

void giro_izq90(){
	setup_timer_2(T2_DIV_BY_1,500,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
	setup_ccp1(CCP_PWM);
    setup_ccp2(CCP_PWM);
    set_pwm1_duty(30);
	set_pwm2_duty(70);
	delay_ms(250);
}



void main(){
	set_tris_A(0x0F);
	set_tris_C(0x00);

	setup_adc(ADC_CLOCK_DIV_2);
	setup_adc_ports(3);
	while(1){
		setup_timer_2(T2_DIV_BY_1,1,1); //Modo, periodo y postscaler, para que funciones a 1 Hz
	    setup_ccp1(CCP_PWM);
    	setup_ccp2(CCP_PWM);
		set_pwm1_duty(90);
     	set_pwm2_duty(90);;
        set_adc_channel(AN0);
		delay_ms(1);
		adelante = read_adc();
		volta = adelante* decimal;
        set_adc_channel(1);
	    delay_ms(1);
		izq = read_adc();
        volti = izq* decimal;
        set_adc_channel(2);
		delay_ms(1);
		der = read_adc();
		voltd = der* decimal;
        if ((Volta >0.5) && (volta<2.7)){
                disa=(((16.75*pow(volta,4.0))-119.26*pow(volta,3.0))+(311.7*pow(volta,2.0))-(365.71*volta)+184.03);
                        if (disa<10.0){
                                        
                                if ((volti >0.5) && (volti<2.7)){
                                            disi=(((16.75*pow(volti,4.0))-119.26*pow(volti,3.0))+(311.7*pow(volti,2.0))-(365.71*volti)+184.03);
                                            if (disi<10.0){ 
                                            if ((voltd >0.5) && (voltd<2.7)){
                                            disd=(((16.75*pow(voltd,4.0))-119.26*pow(voltd,3.0))+(311.7*pow(voltd,2.0))-(365.71*voltd)+184.03);
                                            }if (disd<10.0){ 
                                                   giro_180();
                                            }else {giro_der90();}

                                     }else{
                                          giro_izq90();  
                                                        }
				                }
                        } else{ 
                          break;
																								}
                        }
           
                
       else{ 
           if ((volti >0.5) && (volti<2.7)){
                disi=(((16.75*pow(volti,4.0))-119.26*pow(volti,3.0))+(311.7*pow(volti,2.0))-(365.71*volti)+184.03);
                if (disi<10.0){
                giro_der90();
                }
        }
        else{
              if ((voltd >0.5) && (voltd<2.7)){
                       disd=(((16.75*pow(voltd,4.0))-119.26*pow(voltd,3.0))+(311.7*pow(voltd,2.0))-(365.71*voltd)+184.03);
                       if (disd<10.0){ 
                          giro_izq90();
                       }
              }
            }      
        }
 }  
}