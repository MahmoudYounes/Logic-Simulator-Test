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

class ApplicationManagerTest : public ::testing::Test {

};



// testing applicationmanager class
/*
 * methods that will not be tested due to it's dependency on gui purly:
 * - UpdateInterface
 * - 
 *
 *
 *
 */
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

TEST(ApplicationManagerTest, TestConstructor){
	ApplicationManager appman;
	Component** mcmp = appman.GetComponentList();
	EXPECT_EQ(appman.GetExistingComponentsCount(), 0);
	EXPECT_EQ(appman.GetCopiedComp(), (Component*) NULL);
	EXPECT_TRUE(appman.GetOutput() != NULL);
	EXPECT_TRUE(appman.GetInput() != NULL);
}

/* Testing the get user action Function with it's sub function Input::getUserAction*/
TEST(ApplicationManagerTest, TestGetUserActionExit){
	cout << "Expecting exit action.\n";
	
	ApplicationManager AppManager;
	window *w = AppManager.GetOutput()->GetCurrentWindow();
	ActionType oldAction = ActionType::HOVER, newAction;
	do {
		w->SetUserClick(649, 49);
		newAction = AppManager.GetUserAction();
		if (oldAction != newAction) break;
		oldAction = newAction;
		AppManager.UpdateInterface();
	} while (newAction != ActionType::EXIT);
	EXPECT_TRUE(newAction == ActionType::EXIT);
}

TEST(ApplicationManagerTest, TestSetGetCopiedComp){
	ApplicationManager appman;
	GraphicsInfo gfx;
	
	Component* comp = new AND(appman.GetOutput(), gfx, 1);
	appman.SetCopiedComp(comp);
	EXPECT_TRUE(comp == appman.GetCopiedComp());
}


// ================================================================================= \\
