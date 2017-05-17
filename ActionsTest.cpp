#pragma once

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

TEST(TestActions, TestAddGate){
	ApplicationManager apm;
	window *w = apm.GetOutput()->GetCurrentWindow();

	GraphicsInfo g1;
	g1.x1 = 15;
	g1.y1 = UI.GateBarHeight + UI.ToolBarHeight + 15;
	g1.x2 = 15;
	g1.y2 = UI.GateBarHeight + UI.ToolBarHeight + 15;

	GraphicsInfo g2;
	g2.x1 = 30;
	g2.y1 = UI.GateBarHeight + UI.ToolBarHeight + 30;
	g2.x2 = 30;
	g2.y2 = UI.GateBarHeight + UI.ToolBarHeight + 30;

	Data *dm = new Data();
	dm->GfxInfo = g1;
	dm->Label = "test";
	Component *c1 = new AND(apm.GetOutput(), g1, 1);
	Component *c2 = new AND(apm.GetOutput(), g2, 1);
	apm.AddComponent(c1);
	apm.AddComponent(c2);
	// should try various action types.
	// error in actiontype can be undo given the gate
	w->SetUserClick(50, UI.GateBarHeight + UI.ToolBarHeight + 50);
	Action *a = new AddGate(&apm, ActionType::ADD_GATE_AND);
	EXPECT_TRUE(a != NULL);
	EXPECT_TRUE(a->ReadActionParameters());

	Component **clist = apm.GetComponentList();
	clist[0]->Delete(apm.GetOutput());

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



	delete a;
	a = new AddGate(&apm, ActionType::EXIT);

	EXPECT_TRUE(a != NULL);
	w->SetUserClick(15, UI.GateBarHeight + UI.ToolBarHeight + 15);
	w->SetUserClick(30, 30 + UI.GateBarHeight + UI.ToolBarHeight);
	EXPECT_FALSE(a->ReadActionParameters());
	w->WaitMouseClick(tx, ty);
	w->WaitMouseClick(tx, ty);


	delete b;
	b = new AddConnection(&apm, dm);
	EXPECT_TRUE(b != NULL);
	w->SetUserClick(15, UI.GateBarHeight + UI.ToolBarHeight + 15);
	w->SetUserClick(30, 30 + UI.GateBarHeight + UI.ToolBarHeight);
	EXPECT_FALSE(b->ReadActionParameters());
	w->WaitMouseClick(tx, ty);
	w->WaitMouseClick(tx, ty);

	///////////////////////////////
	c1 = new AND(apm.GetOutput(), g1, 1);
	c2 = new AND(apm.GetOutput(), g2, 1);


	EXPECT_FALSE(a->Execute());
	w->SetUserClick(15, UI.GateBarHeight + UI.ToolBarHeight + 15);
	apm.AddComponent(c1);
	EXPECT_FALSE(a->Execute());

	w->SetUserClick(15, UI.GateBarHeight + UI.ToolBarHeight + 15);
	w->SetUserClick(30, 30 + UI.GateBarHeight + UI.ToolBarHeight);
	apm.AddComponent(c2);
	EXPECT_TRUE(a->Execute());
}
//
TEST(TestActions, TestCopy){
	ApplicationManager apm;
	window *w = apm.GetOutput()->GetCurrentWindow();
	Action *a = new Copy(&apm);
	EXPECT_FALSE(a->ReadActionParameters());
	EXPECT_FALSE(a->Execute());

	GraphicsInfo gfx1, gfx2;
	gfx1.x1 = 150;
	gfx1.y1 = 150;
	gfx1.x2 = 150 + UI.PinOffset;
	gfx1.y2 = 150 + UI.PinOffset;

	gfx2.x1 = 200;
	gfx2.y1 = 200;
	gfx2.x2 = 200 + UI.PinOffset;
	gfx2.y2 = 200 + UI.PinOffset;
	vector<GraphicsInfo> gfxvec;
	gfxvec.push_back(gfx1);
	gfxvec.push_back(gfx2);
	Component *c = new Connection(apm.GetOutput(), gfx1, gfxvec);
	apm.AddComponent(c);
	w->SetUserClick(150, 150);
	//w->SetUserClick(30, 30 + UI.GateBarHeight + UI.ToolBarHeight);
	EXPECT_FALSE(a->ReadActionParameters());
	EXPECT_FALSE(a->Execute());

	c->Delete(apm.GetOutput());
	c = new AND(apm.GetOutput(), gfx1, 1);
	apm.AddComponent(c);
	EXPECT_TRUE(a->ReadActionParameters());
	EXPECT_TRUE(a->Execute());
}

TEST(TestActions, TestCut){
	ApplicationManager apm;
	window *w = apm.GetOutput()->GetCurrentWindow();
	Action *a = new Cut(&apm);
	EXPECT_FALSE(a->ReadActionParameters());
	EXPECT_FALSE(a->Execute());

	GraphicsInfo gfx1, gfx2;
	gfx1.x1 = 150;
	gfx1.y1 = 150;
	gfx1.x2 = 150 + UI.PinOffset;
	gfx1.y2 = 150 + UI.PinOffset;
	vector<GraphicsInfo> gfxvec;
	gfxvec.push_back(gfx1);
	gfxvec.push_back(gfx2);
	Component *c = new Connection(apm.GetOutput(), gfx1, gfxvec);
	apm.AddComponent(c);
	w->SetUserClick(150, 150);
	EXPECT_FALSE(a->ReadActionParameters());
	EXPECT_FALSE(a->Execute());

	c->Delete(apm.GetOutput());

	c = new AND(apm.GetOutput(), gfx1, 1);
	apm.AddComponent(c);
	EXPECT_TRUE(a->ReadActionParameters());
	EXPECT_TRUE(a->Execute());
}


TEST(TestActions, TestDelete){
	ApplicationManager apm;
	window *w = apm.GetOutput()->GetCurrentWindow();
	Action *a = new Delete(&apm);

	GraphicsInfo gfx1, gfx2;
	gfx1.x1 = 150;
	gfx1.y1 = 150;
	gfx1.x2 = 150 + UI.PinOffset;
	gfx1.y2 = 150 + UI.PinOffset;
	vector<GraphicsInfo> gfxvec;
	gfxvec.push_back(gfx1);
	gfxvec.push_back(gfx2);
	Component *c = new AND(apm.GetOutput(), gfx1, 1);
	c->SetSelected(true);

	EXPECT_FALSE(a->ReadActionParameters());
	EXPECT_FALSE(a->Execute());

	apm.AddComponent(c);
	EXPECT_TRUE(a->ReadActionParameters());
	EXPECT_TRUE(a->Execute());
}

TEST(TestActions, TestEdit){
	ApplicationManager apm;
	GraphicsInfo gfx1, gfx2;
	gfx1.x1 = 150;
	gfx1.y1 = 150;
	gfx1.x2 = 150 + UI.PinOffset;
	gfx1.y2 = 150 + UI.PinOffset;

	gfx1.x1 = 200;
	gfx1.y1 = 200;
	gfx1.x2 = 200 + UI.PinOffset;
	gfx1.y2 = 200 + UI.PinOffset;
	vector<GraphicsInfo> gfxvec;
	gfxvec.push_back(gfx1);
	gfxvec.push_back(gfx2);
	Component *c = new AND(apm.GetOutput(), gfx1, 1);
	apm.AddComponent(c);
	Action *a = new Edit(&apm);

	apm.GetOutput()->GetCurrentWindow()->SetUserClick(0, 0);
	EXPECT_FALSE(a->Execute());
	apm.GetOutput()->GetCurrentWindow()->SetUserClick(100, 100);
	EXPECT_FALSE(a->Execute());
	apm.GetOutput()->GetCurrentWindow()->SetUserClick(155, 155);
	EXPECT_TRUE(a->Execute());

	c = new Connection(apm.GetOutput(), gfx1, gfxvec);
	apm.AddComponent(c);
	apm.GetOutput()->GetCurrentWindow()->SetUserClick(150, 150);
	EXPECT_TRUE(a->Execute());
}
