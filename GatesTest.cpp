#pragma once

#include <fstream>
#include <string.h>

#include "gtest/gtest.h"
#include "ApplicationManager.h"
#include "Components\AND.h"
#include "Components\AND3.h"
#include "Components\Buffer.h"
#include "Components\NAND.h"
#include "Components\NOR.h"
#include "Components\NOR3.h"
#include "Components\NOT.h"
#include "Components\OR.h"
#include "Components\XNOR.h"
#include "Components\XOR.h"
#include "Components\XOR3.h"


class AndGateTest : public ::testing::Test 
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	AND* andGate;

	virtual void SetUp() 
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		andGate = new AND(output, gfx, 0);
		andGate->SetLabel("AndTest");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete andGate;
	}
};


TEST_F(AndGateTest, CheckingPinsCoordinates)
{
	int xCoord, yCoord;
	
	andGate->GetInputPinCoordinates(xCoord, yCoord, 0);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(58, yCoord);

	andGate->GetInputPinCoordinates(xCoord, yCoord, 1);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(90, yCoord);
}

TEST_F(AndGateTest, NoInputsOperation)
{
	//when nothing is connected to the and gate's
	//input pins, output pin should be low by default
	andGate->Operate();
	EXPECT_EQ(Status::LOW, andGate->GetOutputPinStatus());
}

TEST_F(AndGateTest, LowInputsOperation)
{
	andGate->GetInputPin(0)->SetStatus(Status::LOW);
	andGate->GetInputPin(1)->SetStatus(Status::LOW);

	andGate->Operate();
	EXPECT_EQ(Status::LOW, andGate->GetOutputPinStatus());
}

TEST_F(AndGateTest, HighInputsOperation)
{
	andGate->GetInputPin(0)->SetStatus(Status::HIGH);
	andGate->GetInputPin(1)->SetStatus(Status::HIGH);

	andGate->Operate();
	EXPECT_EQ(Status::HIGH, andGate->GetOutputPinStatus());
}

TEST_F(AndGateTest, MixedInputsOperation)
{
	andGate->GetInputPin(0)->SetStatus(Status::LOW);
	andGate->GetInputPin(1)->SetStatus(Status::HIGH);

	andGate->Operate();
	EXPECT_EQ(Status::LOW, andGate->GetOutputPinStatus());

	andGate->GetInputPin(0)->SetStatus(Status::HIGH);
	andGate->GetInputPin(1)->SetStatus(Status::LOW);

	andGate->Operate();
	EXPECT_EQ(Status::LOW, andGate->GetOutputPinStatus());
}

TEST_F(AndGateTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	andGate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");
	
	string line;
	getline(gateLoadData, line);
	
	EXPECT_EQ("AND AndTest 50 50", line);
}

TEST_F(AndGateTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_AND, andGate->GetAddActionType());
}



class And3GateTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	AND3* and3Gate;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		and3Gate = new AND3(output, gfx, 0);
		and3Gate->SetLabel("And3Test");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete and3Gate;
	}
};

TEST_F(And3GateTest, NoInputsOperation)
{
	and3Gate->Operate();
	EXPECT_EQ(Status::LOW, and3Gate->GetOutputPinStatus());
}

TEST_F(And3GateTest, LowInputsOperation)
{
	and3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	and3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	and3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	and3Gate->Operate();
	EXPECT_EQ(Status::LOW, and3Gate->GetOutputPinStatus());
}

TEST_F(And3GateTest, HighInputsOperation)
{
	and3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	and3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	and3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	and3Gate->Operate();
	EXPECT_EQ(Status::HIGH, and3Gate->GetOutputPinStatus());
}

TEST_F(And3GateTest, MixedInputsOperation)
{
	and3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	and3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	and3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	and3Gate->Operate();
	EXPECT_EQ(Status::LOW, and3Gate->GetOutputPinStatus());

	
	and3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	and3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	and3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	and3Gate->Operate();
	EXPECT_EQ(Status::LOW, and3Gate->GetOutputPinStatus());

	
	and3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	and3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	and3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	and3Gate->Operate();
	EXPECT_EQ(Status::LOW, and3Gate->GetOutputPinStatus());

	
	and3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	and3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	and3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	and3Gate->Operate();
	EXPECT_EQ(Status::LOW, and3Gate->GetOutputPinStatus());


	and3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	and3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	and3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	and3Gate->Operate();
	EXPECT_EQ(Status::LOW, and3Gate->GetOutputPinStatus());


	and3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	and3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	and3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	and3Gate->Operate();
	EXPECT_EQ(Status::LOW, and3Gate->GetOutputPinStatus());
}

TEST_F(And3GateTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	and3Gate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("AND3 And3Test 50 50", line);
}

TEST_F(And3GateTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_AND3, and3Gate->GetAddActionType());
}




class BufferTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	Buffer* buffer;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		buffer = new Buffer(output, gfx, 0);
		buffer->SetLabel("BufferTest");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete buffer;
	}
};


TEST_F(BufferTest, CheckingPinsCoordinates)
{
	int xCoord, yCoord;

	buffer->GetInputPinCoordinates(xCoord, yCoord, 0);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(74, yCoord);
}

TEST_F(BufferTest, NoInputsOperation)
{
	buffer->Operate();
	EXPECT_EQ(Status::LOW, buffer->GetOutputPinStatus());
}

TEST_F(BufferTest, LowInputsOperation)
{
	buffer->GetInputPin(0)->SetStatus(Status::LOW);

	buffer->Operate();
	EXPECT_EQ(Status::LOW, buffer->GetOutputPinStatus());
}

TEST_F(BufferTest, HighInputsOperation)
{
	buffer->GetInputPin(0)->SetStatus(Status::HIGH);

	buffer->Operate();
	EXPECT_EQ(Status::HIGH, buffer->GetOutputPinStatus());
}

TEST_F(BufferTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	buffer->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("BUFFER BufferTest 50 50", line);
}

TEST_F(BufferTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_BUFFER, buffer->GetAddActionType());
}




class NandGateTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	NAND* nandGate;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		nandGate = new NAND(output, gfx, 0);
		nandGate->SetLabel("NandTest");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete nandGate;
	}
};


TEST_F(NandGateTest, CheckingPinsCoordinates)
{
	int xCoord, yCoord;

	nandGate->GetInputPinCoordinates(xCoord, yCoord, 0);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(58, yCoord);

	nandGate->GetInputPinCoordinates(xCoord, yCoord, 1);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(90, yCoord);
}

TEST_F(NandGateTest, NoInputsOperation)
{
	nandGate->Operate();
	EXPECT_EQ(Status::HIGH, nandGate->GetOutputPinStatus());
}

TEST_F(NandGateTest, LowInputsOperation)
{
	nandGate->GetInputPin(0)->SetStatus(Status::LOW);
	nandGate->GetInputPin(1)->SetStatus(Status::LOW);

	nandGate->Operate();
	EXPECT_EQ(Status::HIGH, nandGate->GetOutputPinStatus());
}

TEST_F(NandGateTest, HighInputsOperation)
{
	nandGate->GetInputPin(0)->SetStatus(Status::HIGH);
	nandGate->GetInputPin(1)->SetStatus(Status::HIGH);

	nandGate->Operate();
	EXPECT_EQ(Status::LOW, nandGate->GetOutputPinStatus());
}

TEST_F(NandGateTest, MixedInputsOperation)
{
	nandGate->GetInputPin(0)->SetStatus(Status::LOW);
	nandGate->GetInputPin(1)->SetStatus(Status::HIGH);

	nandGate->Operate();
	EXPECT_EQ(Status::HIGH, nandGate->GetOutputPinStatus());

	nandGate->GetInputPin(0)->SetStatus(Status::HIGH);
	nandGate->GetInputPin(1)->SetStatus(Status::LOW);

	nandGate->Operate();
	EXPECT_EQ(Status::HIGH, nandGate->GetOutputPinStatus());
}

TEST_F(NandGateTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	nandGate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("NAND NandTest 50 50", line);
}

TEST_F(NandGateTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_NAND, nandGate->GetAddActionType());
}




class OrGateTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	OR* orGate;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		orGate = new OR(output, gfx, 0);
		orGate->SetLabel("OrTest");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete orGate;
	}
};


TEST_F(OrGateTest, CheckingPinsCoordinates)
{
	int xCoord, yCoord;

	orGate->GetInputPinCoordinates(xCoord, yCoord, 0);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(58, yCoord);

	orGate->GetInputPinCoordinates(xCoord, yCoord, 1);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(90, yCoord);
}

TEST_F(OrGateTest, NoInputsOperation)
{
	//when nothing is connected to the and gate's
	//input pins, output pin should be low by default
	orGate->Operate();
	EXPECT_EQ(Status::LOW, orGate->GetOutputPinStatus());
}

TEST_F(OrGateTest, LowInputsOperation)
{
	orGate->GetInputPin(0)->SetStatus(Status::LOW);
	orGate->GetInputPin(1)->SetStatus(Status::LOW);

	orGate->Operate();
	EXPECT_EQ(Status::LOW, orGate->GetOutputPinStatus());
}

TEST_F(OrGateTest, HighInputsOperation)
{
	orGate->GetInputPin(0)->SetStatus(Status::HIGH);
	orGate->GetInputPin(1)->SetStatus(Status::HIGH);

	orGate->Operate();
	EXPECT_EQ(Status::HIGH, orGate->GetOutputPinStatus());
}

TEST_F(OrGateTest, MixedInputsOperation)
{
	orGate->GetInputPin(0)->SetStatus(Status::LOW);
	orGate->GetInputPin(1)->SetStatus(Status::HIGH);

	orGate->Operate();
	EXPECT_EQ(Status::HIGH, orGate->GetOutputPinStatus());

	orGate->GetInputPin(0)->SetStatus(Status::HIGH);
	orGate->GetInputPin(1)->SetStatus(Status::LOW);

	orGate->Operate();
	EXPECT_EQ(Status::HIGH, orGate->GetOutputPinStatus());
}

TEST_F(OrGateTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	orGate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("OR OrTest 50 50", line);
}

TEST_F(OrGateTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_OR, orGate->GetAddActionType());
}




class NorGateTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	NOR* norGate;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		norGate = new NOR(output, gfx, 0);
		norGate->SetLabel("NorTest");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete norGate;
	}
};


TEST_F(NorGateTest, CheckingPinsCoordinates)
{
	int xCoord, yCoord;

	norGate->GetInputPinCoordinates(xCoord, yCoord, 0);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(58, yCoord);

	norGate->GetInputPinCoordinates(xCoord, yCoord, 1);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(90, yCoord);
}

TEST_F(NorGateTest, NoInputsOperation)
{
	norGate->Operate();
	EXPECT_EQ(Status::HIGH, norGate->GetOutputPinStatus());
}

TEST_F(NorGateTest, LowInputsOperation)
{
	norGate->GetInputPin(0)->SetStatus(Status::LOW);
	norGate->GetInputPin(1)->SetStatus(Status::LOW);

	norGate->Operate();
	EXPECT_EQ(Status::HIGH, norGate->GetOutputPinStatus());
}

TEST_F(NorGateTest, HighInputsOperation)
{
	norGate->GetInputPin(0)->SetStatus(Status::HIGH);
	norGate->GetInputPin(1)->SetStatus(Status::HIGH);

	norGate->Operate();
	EXPECT_EQ(Status::LOW, norGate->GetOutputPinStatus());
}

TEST_F(NorGateTest, MixedInputsOperation)
{
	norGate->GetInputPin(0)->SetStatus(Status::LOW);
	norGate->GetInputPin(1)->SetStatus(Status::HIGH);

	norGate->Operate();
	EXPECT_EQ(Status::LOW, norGate->GetOutputPinStatus());

	norGate->GetInputPin(0)->SetStatus(Status::HIGH);
	norGate->GetInputPin(1)->SetStatus(Status::LOW);

	norGate->Operate();
	EXPECT_EQ(Status::LOW, norGate->GetOutputPinStatus());
}

TEST_F(NorGateTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	norGate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("NOR NorTest 50 50", line);
}

TEST_F(NorGateTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_NOR, norGate->GetAddActionType());
}





class Nor3GateTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	NOR3* nor3Gate;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		nor3Gate = new NOR3(output, gfx, 0);
		nor3Gate->SetLabel("Nor3Test");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete nor3Gate;
	}
};

TEST_F(Nor3GateTest, NoInputsOperation)
{
	nor3Gate->Operate();
	EXPECT_EQ(Status::HIGH, nor3Gate->GetOutputPinStatus());
}

TEST_F(Nor3GateTest, LowInputsOperation)
{
	nor3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	nor3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	nor3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	nor3Gate->Operate();
	EXPECT_EQ(Status::HIGH, nor3Gate->GetOutputPinStatus());
}

TEST_F(Nor3GateTest, HighInputsOperation)
{
	nor3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	nor3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	nor3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	nor3Gate->Operate();
	EXPECT_EQ(Status::LOW, nor3Gate->GetOutputPinStatus());
}

TEST_F(Nor3GateTest, MixedInputsOperation)
{
	nor3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	nor3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	nor3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	nor3Gate->Operate();
	EXPECT_EQ(Status::LOW, nor3Gate->GetOutputPinStatus());


	nor3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	nor3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	nor3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	nor3Gate->Operate();
	EXPECT_EQ(Status::LOW, nor3Gate->GetOutputPinStatus());


	nor3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	nor3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	nor3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	nor3Gate->Operate();
	EXPECT_EQ(Status::LOW, nor3Gate->GetOutputPinStatus());


	nor3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	nor3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	nor3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	nor3Gate->Operate();
	EXPECT_EQ(Status::LOW, nor3Gate->GetOutputPinStatus());


	nor3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	nor3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	nor3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	nor3Gate->Operate();
	EXPECT_EQ(Status::LOW, nor3Gate->GetOutputPinStatus());


	nor3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	nor3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	nor3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	nor3Gate->Operate();
	EXPECT_EQ(Status::LOW, nor3Gate->GetOutputPinStatus());
}

TEST_F(Nor3GateTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	nor3Gate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("NOR3 Nor3Test 50 50", line);
}

TEST_F(Nor3GateTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_NOR3, nor3Gate->GetAddActionType());
}





class NotTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	NOT* notGate;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		notGate = new NOT(output, gfx, 0);
		notGate->SetLabel("NotTest");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete notGate;
	}
};


TEST_F(NotTest, CheckingPinsCoordinates)
{
	int xCoord, yCoord;

	notGate->GetInputPinCoordinates(xCoord, yCoord, 0);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(74, yCoord);
}

TEST_F(NotTest, NoInputsOperation)
{
	notGate->Operate();
	EXPECT_EQ(Status::HIGH, notGate->GetOutputPinStatus());
}

TEST_F(NotTest, LowInputsOperation)
{
	notGate->GetInputPin(0)->SetStatus(Status::LOW);

	notGate->Operate();
	EXPECT_EQ(Status::HIGH, notGate->GetOutputPinStatus());
}

TEST_F(NotTest, HighInputsOperation)
{
	notGate->GetInputPin(0)->SetStatus(Status::HIGH);

	notGate->Operate();
	EXPECT_EQ(Status::LOW, notGate->GetOutputPinStatus());
}

TEST_F(NotTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	notGate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("NOT NotTest 50 50", line);
}

TEST_F(NotTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_NOT, notGate->GetAddActionType());
}





class XorGateTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	XOR* xorGate;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		xorGate = new XOR(output, gfx, 0);
		xorGate->SetLabel("XorTest");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete xorGate;
	}
};


TEST_F(XorGateTest, CheckingPinsCoordinates)
{
	int xCoord, yCoord;

	xorGate->GetInputPinCoordinates(xCoord, yCoord, 0);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(58, yCoord);

	xorGate->GetInputPinCoordinates(xCoord, yCoord, 1);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(90, yCoord);
}

TEST_F(XorGateTest, NoInputsOperation)
{
	xorGate->Operate();
	EXPECT_EQ(Status::LOW, xorGate->GetOutputPinStatus());
}

TEST_F(XorGateTest, LowInputsOperation)
{
	xorGate->GetInputPin(0)->SetStatus(Status::LOW);
	xorGate->GetInputPin(1)->SetStatus(Status::LOW);

	xorGate->Operate();
	EXPECT_EQ(Status::LOW, xorGate->GetOutputPinStatus());
}

TEST_F(XorGateTest, HighInputsOperation)
{
	xorGate->GetInputPin(0)->SetStatus(Status::HIGH);
	xorGate->GetInputPin(1)->SetStatus(Status::HIGH);

	xorGate->Operate();
	EXPECT_EQ(Status::LOW, xorGate->GetOutputPinStatus());
}

TEST_F(XorGateTest, MixedInputsOperation)
{
	xorGate->GetInputPin(0)->SetStatus(Status::LOW);
	xorGate->GetInputPin(1)->SetStatus(Status::HIGH);

	xorGate->Operate();
	EXPECT_EQ(Status::HIGH, xorGate->GetOutputPinStatus());

	xorGate->GetInputPin(0)->SetStatus(Status::HIGH);
	xorGate->GetInputPin(1)->SetStatus(Status::LOW);

	xorGate->Operate();
	EXPECT_EQ(Status::HIGH, xorGate->GetOutputPinStatus());
}

TEST_F(XorGateTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	xorGate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("XOR XorTest 50 50", line);
}

TEST_F(XorGateTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_XOR, xorGate->GetAddActionType());
}





class Xor3GateTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	XOR3* xor3Gate;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		xor3Gate = new XOR3(output, gfx, 0);
		xor3Gate->SetLabel("Xor3Test");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete xor3Gate;
	}
};

TEST_F(Xor3GateTest, NoInputsOperation)
{
	xor3Gate->Operate();
	EXPECT_EQ(Status::LOW, xor3Gate->GetOutputPinStatus());
}

TEST_F(Xor3GateTest, LowInputsOperation)
{
	xor3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	xor3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	xor3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	xor3Gate->Operate();
	EXPECT_EQ(Status::LOW, xor3Gate->GetOutputPinStatus());
}

TEST_F(Xor3GateTest, HighInputsOperation)
{
	xor3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	xor3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	xor3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	xor3Gate->Operate();
	EXPECT_EQ(Status::HIGH, xor3Gate->GetOutputPinStatus());
}

TEST_F(Xor3GateTest, MixedInputsOperation)
{
	xor3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	xor3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	xor3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	xor3Gate->Operate();
	EXPECT_EQ(Status::HIGH, xor3Gate->GetOutputPinStatus());


	xor3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	xor3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	xor3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	xor3Gate->Operate();
	EXPECT_EQ(Status::HIGH, xor3Gate->GetOutputPinStatus());


	xor3Gate->GetInputPin(0)->SetStatus(Status::LOW);
	xor3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	xor3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	xor3Gate->Operate();
	EXPECT_EQ(Status::LOW, xor3Gate->GetOutputPinStatus());


	xor3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	xor3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	xor3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	xor3Gate->Operate();
	EXPECT_EQ(Status::HIGH, xor3Gate->GetOutputPinStatus());


	xor3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	xor3Gate->GetInputPin(1)->SetStatus(Status::LOW);
	xor3Gate->GetInputPin(2)->SetStatus(Status::HIGH);

	xor3Gate->Operate();
	EXPECT_EQ(Status::LOW, xor3Gate->GetOutputPinStatus());


	xor3Gate->GetInputPin(0)->SetStatus(Status::HIGH);
	xor3Gate->GetInputPin(1)->SetStatus(Status::HIGH);
	xor3Gate->GetInputPin(2)->SetStatus(Status::LOW);

	xor3Gate->Operate();
	EXPECT_EQ(Status::LOW, xor3Gate->GetOutputPinStatus());
}

TEST_F(Xor3GateTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	xor3Gate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("XOR3  Xor3Test 50 50", line);
}

TEST_F(Xor3GateTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_XOR3, xor3Gate->GetAddActionType());
}




class XnorGateTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	Output* output;
	GraphicsInfo gfx;

	XNOR* xnorGate;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		gfx.x1 = 50;
		gfx.x2 = 50;
		gfx.y1 = 50;
		gfx.y2 = 50;

		xnorGate = new XNOR(output, gfx, 0);
		xnorGate->SetLabel("XnorTest");
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete xnorGate;
	}
};


TEST_F(XnorGateTest, CheckingPinsCoordinates)
{
	int xCoord, yCoord;

	xnorGate->GetInputPinCoordinates(xCoord, yCoord, 0);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(58, yCoord);

	xnorGate->GetInputPinCoordinates(xCoord, yCoord, 1);
	EXPECT_EQ(42, xCoord);
	EXPECT_EQ(90, yCoord);
}

TEST_F(XnorGateTest, NoInputsOperation)
{
	xnorGate->Operate();
	EXPECT_EQ(Status::HIGH, xnorGate->GetOutputPinStatus());
}

TEST_F(XnorGateTest, LowInputsOperation)
{
	xnorGate->GetInputPin(0)->SetStatus(Status::LOW);
	xnorGate->GetInputPin(1)->SetStatus(Status::LOW);

	xnorGate->Operate();
	EXPECT_EQ(Status::HIGH, xnorGate->GetOutputPinStatus());
}

TEST_F(XnorGateTest, HighInputsOperation)
{
	xnorGate->GetInputPin(0)->SetStatus(Status::HIGH);
	xnorGate->GetInputPin(1)->SetStatus(Status::HIGH);

	xnorGate->Operate();
	EXPECT_EQ(Status::HIGH, xnorGate->GetOutputPinStatus());
}

TEST_F(XnorGateTest, MixedInputsOperation)
{
	xnorGate->GetInputPin(0)->SetStatus(Status::LOW);
	xnorGate->GetInputPin(1)->SetStatus(Status::HIGH);

	xnorGate->Operate();
	EXPECT_EQ(Status::LOW, xnorGate->GetOutputPinStatus());

	xnorGate->GetInputPin(0)->SetStatus(Status::HIGH);
	xnorGate->GetInputPin(1)->SetStatus(Status::LOW);

	xnorGate->Operate();
	EXPECT_EQ(Status::LOW, xnorGate->GetOutputPinStatus());
}

TEST_F(XnorGateTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	xnorGate->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("XNOR XnorTest 50 50", line);
}

TEST_F(XnorGateTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_GATE_XNOR, xnorGate->GetAddActionType());
}