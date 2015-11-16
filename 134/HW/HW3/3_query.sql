/*1*/
SELECT trade_name,formula FROM Drug,Ph_company WHERE Drug.pname = Ph_company.pname AND Ph_company.pname="Pfizer";
/*2*/
SELECT DISTINCT Drug.pname,Drug.trade_name,Drug.formula FROM Drug,Prescription,Consist_of WHERE Consist_of.dssn = Prescription.dssn AND Drug.trade_name = Consist_of.trade_name;
/*3*/
SELECT Drug.trade_name,Drug.pname,Prescription.pdate FROM Drug,Prescription,Doctor,Consist_of WHERE Doctor.dname = "Elle Elmasri" AND Drug.trade_name = Consist_of.trade_name AND Consist_of.pre_no = Prescription.pre_no AND Prescription.dssn = Doctor.dssn;
/*4*/
SELECT DISTINCT Drug.trade_name,Drug.formula FROM Drug,Sell,Pharmacy WHERE Drug.trade_name = Sell.trade_name AND Pharmacy.name = "CVS" AND Sell.pharmacy_name = Pharmacy.name;
/*5*/
SELECT count(*) AS "Drug Count" FROM Drug,Ph_company WHERE Drug.pname = Ph_company.pname AND Ph_company.pname = "Pfizer";
/*6*/
SELECT Pharmacy.name,Pharmacy.address FROM Pharmacy,Sell WHERE Pharmacy.name = Sell.pharmacy_name AND Sell.trade_name = "Tylenol" AND Sell.price = (SELECT MIN(price) FROM Sell WHERE trade_name = "Tylenol");
/*7*/
SELECT DISTINCT Pharmacy.name FROM Pharmacy,Sell WHERE Pharmacy.name = Sell.pharmacy_name AND (SELECT count(*) FROM Sell WHERE Pharmacy.name = Sell.pharmacy_name) > 2;
