/***********************************************************************
Vczh Library++ 3.0
Developer: Zihan Chen(vczh)
GacUI::Composition System

Interfaces:
***********************************************************************/

#ifndef VCZH_PRESENTATION_ELEMENTS_GUIGRAPHICSRESPONSIVECOMPOSITION
#define VCZH_PRESENTATION_ELEMENTS_GUIGRAPHICSRESPONSIVECOMPOSITION

#include "GuiGraphicsBasicComposition.h"

namespace vl
{
	namespace presentation
	{
		namespace compositions
		{
			enum class ResponsiveDirection
			{
				Horizontal = 1,
				Vertical = 2,
				Both = 3,
			};

			/// <summary>Base class for responsive layout compositions.</summary>
			class GuiResponsiveCompositionBase abstract : public GuiBoundsComposition, public Description<GuiResponsiveCompositionBase>
			{
			protected:
				GuiResponsiveCompositionBase*	responsiveParent = nullptr;
				ResponsiveDirection				direction = ResponsiveDirection::Both;

				void							OnParentLineChanged()override;
				void							NotifyLevelUpdated();

				virtual void					OnResponsiveChildInserted(GuiResponsiveCompositionBase* child);
				virtual void					OnResponsiveChildRemoved(GuiResponsiveCompositionBase* child);
				virtual void					OnResponsiveChildLevelUpdated();

			public:
				GuiResponsiveCompositionBase();
				~GuiResponsiveCompositionBase();

				virtual vint					GetLevelCount() = 0;
				virtual vint					GetCurrentLevel() = 0;
				virtual bool					LevelDown() = 0;
				virtual bool					LevelUp() = 0;

				ResponsiveDirection				GetDirection();
				void							SetDirection(ResponsiveDirection value);
			};

			class GuiResponsiveSharedCollection : public collections::ObservableListBase<controls::GuiControl*>
			{
			};

			class GuiResponsiveViewCollection : public collections::ObservableListBase<GuiResponsiveCompositionBase*>
			{
			};

			class GuiResponsiveSharedComposition : public GuiBoundsComposition, public Description<GuiResponsiveSharedComposition>
			{
			public:
				GuiResponsiveSharedComposition(controls::GuiControl* _shared);
				~GuiResponsiveSharedComposition();
			};

			/// <summary>A responsive layout composition defined by views of different sizes.</summary>
			class GuiResponsiveViewComposition : public GuiResponsiveCompositionBase, public Description<GuiResponsiveViewComposition>
			{
			protected:
				vint								levelCount = 1;
				vint								currentLevel = 0;
				GuiResponsiveSharedCollection		sharedControls;
				GuiResponsiveViewCollection			views;

				void								CalculateLevelCount();
				void								CalculateCurrentLevel();
				void								OnResponsiveChildLevelUpdated();

			public:
				GuiResponsiveViewComposition();
				~GuiResponsiveViewComposition();

				vint																GetLevelCount()override;
				vint																GetCurrentLevel()override;
				bool																LevelDown()override;
				bool																LevelUp()override;

				collections::ObservableListBase<controls::GuiControl*>&				GetSharedControls();
				collections::ObservableListBase<GuiResponsiveCompositionBase*>&		GetViews();
			};

			/// <summary>A responsive layout composition which stop parent responsive composition to search its children.</summary>
			class GuiResponsiveFixedComposition : public GuiResponsiveCompositionBase, public Description<GuiResponsiveFixedComposition>
			{
			public:
				GuiResponsiveFixedComposition();
				~GuiResponsiveFixedComposition();

				vint					GetLevelCount()override;
				vint					GetCurrentLevel()override;
				bool					LevelDown()override;
				bool					LevelUp()override;
			};

			/// <summary>A responsive layout composition which change its size by changing children's views one by one in one direction.</summary>
			class GuiResponsiveStackComposition : public GuiResponsiveCompositionBase, public Description<GuiResponsiveStackComposition>
			{
				using ResponsiveChildList = collections::List<GuiResponsiveCompositionBase*>;
			protected:
				vint					levelCount = 1;
				vint					currentLevel = 0;
				ResponsiveChildList		responsiveChildren;

				void					CalculateLevelCount();
				void					CalculateCurrentLevel();
				void					OnResponsiveChildInserted(GuiResponsiveCompositionBase* child);
				void					OnResponsiveChildRemoved(GuiResponsiveCompositionBase* child);
				void					OnResponsiveChildLevelUpdated();
				bool					ChangeLevel(bool levelDown);

			public:
				GuiResponsiveStackComposition();
				~GuiResponsiveStackComposition();

				vint					GetLevelCount()override;
				vint					GetCurrentLevel()override;
				bool					LevelDown()override;
				bool					LevelUp()override;
			};

			/// <summary>A responsive layout composition which change its size by changing children's views at the same time.</summary>
			class GuiResponsiveGroupComposition : public GuiResponsiveCompositionBase, public Description<GuiResponsiveGroupComposition>
			{
				using ResponsiveChildList = collections::List<GuiResponsiveCompositionBase*>;
			protected:
				vint					levelCount = 1;
				vint					currentLevel = 0;
				ResponsiveChildList		responsiveChildren;

				void					CalculateLevelCount();
				void					CalculateCurrentLevel();
				void					OnResponsiveChildInserted(GuiResponsiveCompositionBase* child);
				void					OnResponsiveChildRemoved(GuiResponsiveCompositionBase* child);
				void					OnResponsiveChildLevelUpdated();

			public:
				GuiResponsiveGroupComposition();
				~GuiResponsiveGroupComposition();

				vint					GetLevelCount()override;
				vint					GetCurrentLevel()override;
				bool					LevelDown()override;
				bool					LevelUp()override;
			};
		}
	}
}

#endif