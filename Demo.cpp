#include "gtest\gtest.h"
#include "ApplicationManager.h"
#include "Utilities\Defs.h"
#include "GUI\Input.h"
#include "GUI\Output.h"
#include "Components\Component.h"
#include "Components\Gate.h"
#include "Components\Connection.h"
#include "Components\Switch.h"
#include "Components\LED.h"
#include "Components\AND.h"
#include "CMUgraphicsLib\colors.h"

#include "Actions\Action.h"
#include "Actions\AddConnection.h"
#include "Actions\AddGate.h"
#include "Actions\Copy.h"
#include "Actions\Cut.h"
#include "Actions\Delete.h"
#include "Actions\Edit.h"
#include "Actions\Exit.h"
#include "Actions\Hover.h"
#include "Actions\LoadAction.h"
#include "Actions\Move.h"
#include "Actions\Paste.h"
#include "Actions\RedoAction.h"
#include "Actions\SaveAction.h"
#include "Actions\Select.h"
#include "Actions\Simulate.h"
#include "Actions\TruthTable.h"
#include "Actions\UndoAction.h"

#include "TestUtils.h"
// testing Actions


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


bool compareColors(color c1, color c2){
	if (c1.ucBlue == c2.ucBlue && c1.ucGreen == c2.ucGreen && c1.ucRed == c2.ucRed)
		return true;
	return false;
}
TEST(OutputTest, TestOutputConstructor){
	Output* o = new Output();

	EXPECT_TRUE(UI.AppMode == Mode::DESIGN);

	EXPECT_TRUE(compareColors(UI.BackgroundColor, color(117, 117, 117)));
	EXPECT_TRUE(compareColors(UI.DarkColor, color(66, 66, 66)));
	EXPECT_TRUE(compareColors(UI.SelectionColor, color(255, 193, 7)));
	EXPECT_TRUE(compareColors(UI.InvalidColor, color(213, 0, 0)));
	EXPECT_TRUE(compareColors(UI.MsgColor, WHITE));
	EXPECT_TRUE(compareColors(UI.ConnectionColor, BLACK));
	EXPECT_TRUE(compareColors(UI.ConnectionOnColor, color(139, 195, 74)));

	EXPECT_TRUE(o->GetCurrentWindow() != NULL);
}
//
TEST(OutputTest, TestCreateInput){
	Output *out = new Output();
	ASSERT_TRUE(out->CreateInput() != NULL);
}
//
TEST(TestActions, TestAddConnection){
	ApplicationManager apm;
	window *w = apm.GetOutput()->GetCurrentWindow();
	GraphicsInfo g1;
	g1.x1 = 15;
	g1.y1 = UI.GateBarHeight + UI.ToolBarHeight + 15;
	g1.x2 = 15 + UI.PinOffset;
	g1.y2 = UI.GateBarHeight + UI.ToolBarHeight + 15 + UI.PinOffset;

	GraphicsInfo g2;
	g2.x1 = 30;
	g2.y1 = UI.GateBarHeight + UI.ToolBarHeight + 30;
	g2.x2 = 30 + UI.PinOffset;
	g2.y2 = UI.GateBarHeight + UI.ToolBarHeight + 30 + UI.PinOffset;


	Data *dm = new Data();
	dm->GfxInfo = g1;
	dm->Label = "test";
	Component *c1 = new AND(apm.GetOutput(), g1, 1);
	Component *c2 = new AND(apm.GetOutput(), g2, 1);
	apm.AddComponent(c1);
	apm.AddComponent(c2);
	Action *a = new AddConnection(&apm, NULL);
	EXPECT_TRUE(a != NULL);
	w->SetUserClick(15, UI.GateBarHeight + UI.ToolBarHeight + 15);
	w->SetUserClick(30, 30 + UI.GateBarHeight + UI.ToolBarHeight);
	EXPECT_TRUE(a->ReadActionParameters());

	Component **clist = apm.GetComponentList();
	clist[0]->Delete(apm.GetOutput());
	w->SetUserClick(15, UI.GateBarHeight + UI.ToolBarHeight + 15);
	EXPECT_FALSE(a->ReadActionParameters());
	clist[1]->Delete(apm.GetOutput());

	EXPECT_FALSE(a->ReadActionParameters());

	Action *b = new AddConnection(&apm, dm);
	EXPECT_TRUE(b != NULL);
	w->SetUserClick(15, UI.GateBarHeight + UI.ToolBarHeight + 15);
	w->SetUserClick(30, 30 + UI.GateBarHeight + UI.ToolBarHeight);
	EXPECT_FALSE(b->ReadActionParameters());
	int tx, ty;
	w->WaitMouseClick(tx, ty);
	w->WaitMouseClick(tx, ty);

	///////////////////////////////
	c1 = new AND(apm.GetOutput(), g1, 1);
	c2 = new AND(apm.GetOutput(), g2, 1);
	apm.AddComponent(c1);
	w->SetUserClick(15, UI.GateBarHeight + UI.ToolBarHeight + 15);
	EXPECT_FALSE(a->Execute());

	w->SetUserClick(15, UI.GateBarHeight + UI.ToolBarHeight + 15);
	w->SetUserClick(30, 30 + UI.GateBarHeight + UI.ToolBarHeight);
	apm.AddComponent(c2);
	EXPECT_TRUE(a->Execute());
}


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

TEST(ApplicationManagerTest, TestAddComponent){
	ApplicationManager appman;
	GraphicsInfo g(2, 3, 4, 5);

	Component *c = new AND(appman.GetOutput(), g, 1);
	Component **clist;
	int x = appman.GetExistingComponentsCount();
	appman.AddComponent(c);

	ASSERT_TRUE(x + 1 == appman.GetExistingComponentsCount());
	ASSERT_TRUE(appman.GetComponentList()[0] == c);
}
//
TEST(ApplicationManagerTest, TestGetExistingComponentsCount){
	ApplicationManager a;
	GraphicsInfo g(2, 3, 4, 5);

	Component *c = new AND(a.GetOutput(), g, 1);
	Component **clist;
	a.AddComponent(c);

	clist = a.GetComponentList();
	clist[0]->Delete(a.GetOutput());
	ASSERT_EQ(a.GetExistingComponentsCount(), 0);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}