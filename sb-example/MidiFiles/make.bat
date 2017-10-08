midicvt otvet.mid otvet_.mid 
midicvt EndMinus.mid EndMinus_.mid
midicvt EndPlus.mid  EndPlus_.mid 
midicvt EndPlus1.mid EndPlus1_.mid 
midicvt EndPlus2.mid EndPlus2_.mid 
midicvt EndPlus3.mid EndPlus3_.mid 
midicvt salu.mid     salu_.mid
midicvt Kolibeln.mid Kolibeln_.mid
midicvt 01.mid 01_.mid

sbc -Obg.sbk otvet_.mid EndMinus_.mid EndPlus_.mid EndPlus1_.mid EndPlus2_.mid EndPlus3_.mid
sbc -Odemo.sbk Kolibeln_.mid salu_.mid 01_.mid
copy bg.sbk ..\bg.sbk
copy demo.sbk ..\demo.sbk
 