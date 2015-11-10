CREATE TABLE Doctor (
	dssn VARCHAR(9) NOT NULL,
	dname VARCHAR(32) NOT NULL,
	specialty VARCHAR(32) NULL,
	PRIMARY KEY (dssn),
	UNIQUE (dssn)
);

CREATE TABLE Prescription(
	dssn VARCHAR(9) NOT NULL,
	pre_no VARCHAR(9) NOT NULL,
	pdate Date NOT NULL,
	PRIMARY KEY (dssn,pre_no),
	UNIQUE (pre_no),
	FOREIGN KEY (dssn) REFERENCES Doctor(dssn)
);

CREATE TABLE Ph_company(
	pname VARCHAR(32) NOT NULL,
	phone VARCHAR(10) NULL,
	UNIQUE (pname)
);

CREATE TABLE Drug(
	pname VARCHAR(32) NOT NULL,
	trade_name VARCHAR(32) NOT NULL,
	formula VARCHAR(9) NOT NULL,
	PRIMARY KEY (pname,trade_name),
	UNIQUE (pname),
	FOREIGN KEY (pname) REFERENCES Ph_company(pname)
);

CREATE TABLE Consist_of(
	dssn VARCHAR(9) NOT NULL,
	pre_no VARCHAR(9) NOT NULL,
	pname VARCHAR(32) NOT NULL,
	trade_name VARCHAR(32) NOT NULL,
	PRIMARY KEY (dssn,pre_no,pname,trade_name),
	FOREIGN KEY (dssn,pre_no) REFERENCES Prescription(dssn,pre_no),
	FOREIGN KEY (pname,trade_name) REFERENCES Drug(pname,trade_name)
);

CREATE TABLE Pharmacy(
	name VARCHAR(32) NOT NULL,
	address VARCHAR(32) NULL,
	phone VARCHAR(10) NULL,
	UNIQUE (name)
);

CREATE TABLE Sell (
	pharmacy_name VARCHAR(32) NOT NULL,
	pname VARCHAR(32) NOT NULL,
	trade_name VARCHAR(32) NOT NULL,
	price VARCHAR(16) NOT NULL,
	FOREIGN KEY (pname, trade_name) REFERENCES Drug(pname, trade_name) ,
	FOREIGN KEY (pharmacy_name) REFERENCES Pharmacy(name) 
);
