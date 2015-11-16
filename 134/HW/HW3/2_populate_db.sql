INSERT INTO Ph_company values("Pfizer","7078889999");
INSERT INTO Ph_company values("USA Drug Co","7076669999");
INSERT INTO Ph_company values("Drugs R Us","7075559999");

INSERT INTO Drug values("Pfizer","Oxycontin","C18H21NO4");
INSERT INTO Drug values("Pfizer","PooStopper","FIBER10");
INSERT INTO Drug values("USA Drug Co","Marijuana","THC");
INSERT INTO Drug values("USA Drug Co","Oxysnifftium","SNIFFHAIR");
INSERT INTO Drug values("Drugs R Us","Cellphonium","TOAST");
INSERT INTO Drug values("Drugs R Us","Tylenol","Magic");
INSERT INTO Drug values("Drugs R Us","Notadrugium","C2H23N12");

INSERT INTO Doctor values("333333333","Dr. Sirius","Sleep Studies");
INSERT INTO Doctor values("444444444","Dr. Snifferdink ","Diet Studies");
INSERT INTO Doctor values("555555555","Dr. Roo","Mood Studies");
INSERT INTO Doctor values("222222222","Dr. Poosh","Survivability");
INSERT INTO Doctor values("666666222","Elle Elmasri","Teacher");

INSERT INTO Prescription values("333333333","1","2015-10-3");
INSERT INTO Prescription values("444444444","2","2015-10-5");
INSERT INTO Prescription values("555555555","3","2015-10-5");
INSERT INTO Prescription values("222222222","4","2015-11-5");
INSERT INTO Prescription values("555555555","5","2015-11-8");
INSERT INTO Prescription values("222222222","6","2015-12-9");
INSERT INTO Prescription values("222222222","7","2015-1-6");
INSERT INTO Prescription values("666666222","8","2015-10-5");
INSERT INTO Prescription values("666666222","9","2015-11-5");
INSERT INTO Prescription values("666666222","10","2015-11-8");

INSERT INTO Consist_of values("333333333","1","Pfizer","Oxycontin");
INSERT INTO Consist_of values("444444444","2","Pfizer","Oxycontin");
INSERT INTO Consist_of values("555555555","5","Pfizer","Oxycontin");
INSERT INTO Consist_of values("555555555","3","USA Drug Co","Oxysnifftium");
INSERT INTO Consist_of values("222222222","4","USA Drug Co","Marijuana");
INSERT INTO Consist_of values("222222222","6","Drugs R Us","Tylenol");
INSERT INTO Consist_of values("222222222","7","Drugs R Us","Notadrugium");
INSERT INTO Consist_of values("666666222","8","Pfizer","Oxycontin");
INSERT INTO Consist_of values("666666222","9","USA Drug Co","Oxysnifftium");
INSERT INTO Consist_of values("666666222","10","USA Drug Co","Marijuana");

INSERT INTO Pharmacy values("Walmart","123 Fake St","7074561237");
INSERT INTO Pharmacy values("CVS","321 Front Dr","4561237894");
INSERT INTO Pharmacy values("Walgreens","456 Rear Ct","0987654356");
INSERT INTO Pharmacy values("Joe's Drugs","789 Side Alley","0987654356");
INSERT INTO Pharmacy values("Connie's Crack House","222 Back Door","0987654356");

INSERT INTO Sell values("Walgreens","Pfizer","Oxycontin",19.99);
INSERT INTO Sell values("Walmart","Pfizer","Oxycontin",18.99);
INSERT INTO Sell values("CVS","Pfizer","Oxycontin",21.99);
INSERT INTO Sell values("Walgreens","Drugs R Us","Cellphonium",128.99);
INSERT INTO Sell values("Walmart","Drugs R Us","Notadrugium",23.99);
INSERT INTO Sell values("CVS","USA Drug Co","Marijuana",20.00);
INSERT INTO Sell values("Walgreens","Drugs R Us","Tylenol",88.99);
INSERT INTO Sell values("CVS","Drugs R Us","Tylenol",23.99);
INSERT INTO Sell values("Walmart","Drugs R Us","Tylenol",26.99);
INSERT INTO Sell values("Joe's Drugs","Drugs R Us","Tylenol",21.99);
INSERT INTO Sell values("Connie's Crack House","USA Drug Co","Marijuana",15.00);
INSERT INTO Sell values("Connie's Crack House","Pfizer","Oxycontin",15.00);
