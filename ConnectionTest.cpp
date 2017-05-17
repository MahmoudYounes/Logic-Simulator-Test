#include <fstream>
#include <string.h>
#include <vector>

#include "gtest/gtest.h"
#include "ApplicationManager.h"

#include "Components\Connection.h"
#include "Components\AND.h"
#include "Components\NOT.h"


class ConnectionTest : public ::testing::Test
{
public:
	ApplicationManager* appManager;
	
	Output* output;
	GraphicsInfo gfx;
	vector<GraphicsInfo> connectionPath;
	
	Connection* connection;

	virtual void SetUp()
	{
		appManager = new ApplicationManager();
		output = new Output();

		connection = new Connection(output, gfx, connectionPath);
	}

	virtual void TearDown()
	{
		delete appManager;
		delete output;
		delete connection;
	}
};

TEST_F(ConnectionTest, SettingSourcePin)
{
	GraphicsInfo andGateGfx;

	AND* noFanoutAnd = new AND(output, andGateGfx, 0);
	
	connection->SetSourcePin(noFanoutAnd->GetOutputPin());

	EXPECT_EQ(connection->GetSourcePin(), noFanoutAnd->GetOutputPin());
	EXPECT_EQ(NULL, noFanoutAnd->GetOutputPin()->GetConnection(0));
	
	
	AND* fanoutAnd = new AND(output, andGateGfx, 2);

	connection->SetSourcePin(fanoutAnd->GetOutputPin());

	EXPECT_EQ(connection->GetSourcePin(), fanoutAnd->GetOutputPin());
	EXPECT_EQ(connection, fanoutAnd->GetOutputPin()->GetConnection(0));
}

TEST_F(ConnectionTest, SettingDestinationPin)
{
	GraphicsInfo andGateGfx;

	AND* andGate = new AND(output, andGateGfx, 0);

	connection->SetDestinationPin(andGate->GetInputPin(1), 1);

	EXPECT_EQ(1, connection->GetDestinationPinIndex());
	EXPECT_EQ(connection->GetDestinationPin(), andGate->GetInputPin(1));
	EXPECT_EQ(connection, andGate->GetInputPin(1)->GetConnection(0));
	EXPECT_EQ(andGate, connection->GetNextComponent(0));
}

TEST_F(ConnectionTest, ConnectionOperation)
{
	GraphicsInfo notGfx;

	NOT* srcNot = new NOT(output, notGfx, 1);
	NOT* dstNot = new NOT(output, notGfx, 1);

	srcNot->SetInputPinStatus(0, Status::LOW);
	srcNot->Operate();

	connection->SetSourcePin(srcNot->GetOutputPin());
	connection->SetDestinationPin(dstNot->GetInputPin(0), 0);

	connection->Operate();
	dstNot->Operate();

	EXPECT_EQ(Status::HIGH, connection->GetInputPinStatus(0));
	EXPECT_EQ(Status::HIGH, connection->GetOutputPinStatus());
	EXPECT_EQ(Status::LOW, dstNot->GetOutputPinStatus());
}

TEST_F(ConnectionTest, UpdatingPathWithNullPins)
{
	//at first source and dest pins are null, that case should 
	//be handled by returning a false when trying to update path
	EXPECT_FALSE(connection->UpdatePath(output));
}

TEST_F(ConnectionTest, UpdatingPath)
{
	GraphicsInfo notGfx1;
	GraphicsInfo notGfx2;

	notGfx1.x1 = 10;
	notGfx1.x2 = 10;
	notGfx1.y1 = 10;
	notGfx1.y2 = 10;

	notGfx2.x1 = 330;
	notGfx2.x2 = 340;
	notGfx2.y1 = 310;
	notGfx2.y2 = 320;

	NOT* not1 = new NOT(output, notGfx1, 1);
	NOT* not2 = new NOT(output, notGfx2, 1);
	NOT* not3 = new NOT(output, notGfx2, 1);

	connection->SetSourcePin(not1->GetOutputPin());
	connection->SetDestinationPin(not2->GetInputPin(0), 0);
	
	EXPECT_FALSE(connection->UpdatePath(output));

	connection->SetSourcePin(not3->GetOutputPin());

	EXPECT_TRUE(connection->UpdatePath(output));
}

TEST_F(ConnectionTest, Deletion)
{
	GraphicsInfo notGfx;

	NOT* srcNot = new NOT(output, notGfx, 1);
	NOT* dstNot = new NOT(output, notGfx, 1);

	srcNot->SetInputPinStatus(0, Status::LOW);
	srcNot->Operate();

	connection->SetSourcePin(srcNot->GetOutputPin());
	connection->SetDestinationPin(dstNot->GetInputPin(0), 0);

	connection->Operate();
	dstNot->Operate();

	connection->Delete(output);

	srcNot->Operate();
	connection->Operate();
	dstNot->Operate();

	EXPECT_EQ(NULL, srcNot->GetOutputPin()->GetConnection(0));
	EXPECT_EQ(NULL, dstNot->GetInputPin(0)->GetConnection(0));
	EXPECT_EQ(Status::HIGH, dstNot->GetOutputPinStatus());
}

TEST_F(ConnectionTest, Restoration)
{
	GraphicsInfo notGfx;

	NOT* srcNot = new NOT(output, notGfx, 1);
	NOT* dstNot = new NOT(output, notGfx, 1);

	srcNot->SetInputPinStatus(0, Status::LOW);
	srcNot->Operate();

	connection->SetSourcePin(srcNot->GetOutputPin());
	connection->SetDestinationPin(dstNot->GetInputPin(0), 0);

	connection->Operate();
	dstNot->Operate();

	connection->Delete(output);

	EXPECT_EQ(NULL, srcNot->GetOutputPin()->GetConnection(0));
	EXPECT_EQ(NULL, dstNot->GetInputPin(0)->GetConnection(0));

	connection->Restore(output);

	EXPECT_EQ(connection, srcNot->GetOutputPin()->GetConnection(0));
	EXPECT_EQ(connection, dstNot->GetInputPin(0)->GetConnection(0));
}

TEST_F(ConnectionTest, CheckingSave)
{
	ofstream gateSaveData("TestData.txt");
	gateSaveData.clear();

	connection->Save(gateSaveData);
	gateSaveData.close();

	ifstream gateLoadData("TestData.txt");

	string line;
	getline(gateLoadData, line);

	EXPECT_EQ("CONNECTION Connection -16 0 16 0", line);
}

TEST_F(ConnectionTest, ReturningActionType)
{
	EXPECT_EQ(ActionType::ADD_CONNECTION, connection->GetAddActionType());
}
