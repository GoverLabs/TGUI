/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2019 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_LIST_VIEW_HPP
#define TGUI_LIST_VIEW_HPP


#include <TGUI/CopiedSharedPtr.hpp>
#include <TGUI/Widgets/Scrollbar.hpp>
#include <TGUI/Renderers/ListViewRenderer.hpp>
#include <TGUI/Text.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @brief List view widget
    /// @warning This widget is new and API stability is not yet guaranteed. Functions and their behavior may still change in newer patch releases, based on feedback.
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    class TGUI_API ListView : public Widget
    {
      public:

        typedef std::shared_ptr<ListView> Ptr; ///< Shared widget pointer
        typedef std::shared_ptr<const ListView> ConstPtr; ///< Shared constant widget pointer

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief The text alignment for all texts within a column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        enum class ColumnAlignment
        {
            Left,   ///< Place the text on the left side (default)
            Center, ///< Center the text inside the column
            Right   ///< Place the text on the right side (e.g. for numbers)
        };

        struct Item
        {
            std::vector<Text> texts;
        };

        struct Column
        {
            float width;
            float designWidth;
            Text text;
            ColumnAlignment alignment;
        };


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Default constructor
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListView();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Creates a new list view widget
        /// @return The new list view
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ListView::Ptr create();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Makes a copy of another list view
        ///
        /// @param listView  The other list view
        ///
        /// @return The new list view
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static ListView::Ptr copy(ListView::ConstPtr listView);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer that may be shared with other widgets using the same renderer
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListViewRenderer* getSharedRenderer();
        const ListViewRenderer* getSharedRenderer() const;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the renderer, which gives access to functions that determine how the widget is displayed
        /// @return Temporary pointer to the renderer
        /// @warning After calling this function, the widget has its own copy of the renderer and it will no longer be shared.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ListViewRenderer* getRenderer();
        const ListViewRenderer* getRenderer() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the size of the list view
        ///
        /// @param size  The new size of the list view
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSize(const Layout2d& size) override;
        using Widget::setSize;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds a column
        ///
        /// @param text      The caption of the new column
        /// @param width     Width of the column. Set width to 0 to make it depend on the width of the column caption.
        /// @param alignment The text alignment for all texts in the column
        ///
        /// @return Index of the added column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t addColumn(const sf::String& text, float width = 0, ColumnAlignment alignment = ColumnAlignment::Left);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text of a column
        ///
        /// @param index  Index of the column to change
        /// @param text   Caption of the column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setColumnText(std::size_t index, const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text of a column
        ///
        /// @param index  Index of the column
        ///
        /// @return Caption of the column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getColumnText(std::size_t index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the width of a column
        ///
        /// @param index  Index of the column to change
        /// @param width  Width of the column. Set width to 0 to make it depend on the width of the column caption.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setColumnWidth(std::size_t index, float width);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the width of a column
        ///
        /// @param index  Index of the column
        ///
        /// @return Width of the column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getColumnWidth(std::size_t index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text alignment within a column
        ///
        /// @param columnIndex Index of the column to change
        /// @param alignment   The text alignment for all texts in the column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setColumnAlignment(unsigned int columnIndex, ColumnAlignment alignment);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the current text alignment within a column
        ///
        /// @param columnIndex Index of the column to inspect
        ///
        /// @return Text alignment for all texts in the column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ColumnAlignment getColumnAlignment(unsigned int columnIndex) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all columns
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllColumns();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of columns in the list view
        ///
        /// @return Number of columns
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getColumnCount() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the height of the header row
        ///
        /// @param height  Height of the header or 0 to make the header size depend on the row height
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setHeaderHeight(float height);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the height of the header row
        ///
        /// @param Current height of the header
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float getHeaderHeight() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the header is shown
        ///
        /// @param showHeader  Whether the header containing the column names shoud be visible
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setHeaderVisible(bool showHeader);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the header is shown
        ///
        /// @return Whether the header containing the column names is visible
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getHeaderVisible() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds an item to the list
        ///
        /// @param text  The caption of the item you want to add
        ///
        /// @return Index of the item that was just added
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t addItem(const sf::String& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Adds an item with values for multiple columns to the list
        ///
        /// @param item  Texts for each column
        ///
        /// @return Index of the item that was just added
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t addItem(const std::vector<sf::String>& item);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes the item from the list view
        ///
        /// @param index  Index of the item in the list view
        ///
        /// @return True when the item was removed, false when the index was too high
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool removeItem(std::size_t index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Removes all items from the list
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void removeAllItems();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Selects an item in the list view
        ///
        /// @param index  Index of the item in the list view
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSelectedItem(std::size_t index);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Deselects the selected item
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void deselectItem();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Gets the index of the selected item
        ///
        /// @return The index of the selected item, or -1 when no item was selected
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        int getSelectedItemIndex() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the amount of items in the list view
        ///
        /// @return Number of items inside the list view
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::size_t getItemCount() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves an item in the list
        ///
        /// @param index  The index of the item
        ///
        /// @return Text of the item or an empty string when the index was higher than the amount of items
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        sf::String getItem(std::size_t index) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves the values of all columns for an item in the list
        ///
        /// @param index  The index of the item
        ///
        /// @return Texts of the item for each column or an list of empty strings when the index was too high
        ///
        /// The returned list has the same length as the amount of columns.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<sf::String> getItemRow(std::size_t index) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a list of the texts in the first column for all items in the list view
        ///
        /// @return Texts of the first column of items
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<sf::String> getItems() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns a list of all column values for all items in the list view
        ///
        /// @return Texts of the items and their subitems
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::vector<std::vector<sf::String>> getItemRows() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the height of the items in the list view
        ///
        /// @param itemHeight  The size of a single item in the list
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setItemHeight(unsigned int itemHeight);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the height of the items in the list view
        ///
        /// @return The item height
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getItemHeight() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text size of the items
        ///
        /// @param textSize  The character size of the text
        ///
        /// This will not change the height that each item has. By default (or when passing 0 to this function) the text will
        /// be auto-sized to nicely fit inside this item height.
        ///
        /// @see setItemHeight
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setTextSize(unsigned int textSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text size of the items
        ///
        /// @return The text size
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the text size of the header caption
        ///
        /// @param textSize  The character size of the header text
        ///
        /// By default, header text size is the same as the text size of the items.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setHeaderTextSize(unsigned int textSize);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the text size of the header caption
        ///
        /// @return The header text size
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getHeaderTextSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the width of the column separator
        ///
        /// @param width  Width of the line separating the columns
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setSeparatorWidth(unsigned int width);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the width of the column separator
        ///
        /// @return Width of the line separating the columns
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        unsigned int getSeparatorWidth() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes whether the list view scrolls to the bottom when a new item is added
        ///
        /// @param autoScroll  Should list view scroll to the bottom when new items are added?
        ///
        /// Auto scrolling is enabled by default.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setAutoScroll(bool autoScroll);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the list view scrolls to the bottom when a new item is added
        ///
        /// @return Does the list view scroll to the bottom when new items are added
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool getAutoScroll() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes when the vertical scrollbar should be displayed
        /// @param policy  The policy for displaying the vertical scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setVerticalScrollbarPolicy(Scrollbar::Policy policy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns when the vertical scrollbar should be displayed
        /// @return The policy for displaying the vertical scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Scrollbar::Policy getVerticalScrollbarPolicy() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes when the horizontal scrollbar should be displayed
        /// @param policy  The policy for displaying the horizontal scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setHorizontalScrollbarPolicy(Scrollbar::Policy policy);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns when the horizontal scrollbar should be displayed
        /// @return The policy for displaying the horizontal scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Scrollbar::Policy getHorizontalScrollbarPolicy() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns whether the mouse position (which is relative to the parent widget) lies on top of the widget
        /// @return Is the mouse on top of the widget?
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseOnWidget(Vector2f pos) const override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMousePressed(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void leftMouseReleased(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseMoved(Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        bool mouseWheelScrolled(float delta, Vector2f pos) override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerOnWidget() override;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @internal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void mouseNoLongerDown() override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Draw the widget to a render target
        ///
        /// @param target Render target to draw to
        /// @param states Current render states
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Retrieves a signal based on its name
        ///
        /// @param signalName  Name of the signal
        ///
        /// @return Signal that corresponds to the name
        ///
        /// @throw Exception when the name does not match any signal
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Signal& getSignal(std::string signalName) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Function called when one of the properties of the renderer is changed
        ///
        /// @param property  Lowercase name of the property that was changed
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void rendererChanged(const std::string& property) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Saves the widget as a tree node in order to save it to a file
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        std::unique_ptr<DataIO::Node> save(SavingRenderersMap& renderers) const override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Loads the widget from a tree of nodes
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void load(const std::unique_ptr<DataIO::Node>& node, const LoadingRenderersMap& renderers) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Returns the size without the borders
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Vector2f getInnerSize() const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Create a Text object for an item from the given caption, using the preset color, font, text size and opacity
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Text createText(const sf::String& caption);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Create a Text object for a header text from the given caption, using the preset color, font, text size and opacity
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Text createHeaderText(const sf::String& caption);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes the color of all Text objects in an item
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void setItemColor(std::size_t index, const Color& color);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Calculate the width of the column based on its caption when no column width was provided
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        float calculateAutoColumnWidth(const Text& text);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the colors of the selected and hovered items
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelectedAndhoveredItemColors();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update the color of all the items
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateItemColors();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Changes the color of all header texts
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateHeaderTextsColor();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update on which item the mouse is standing
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateHoveredItem(int item);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Update which item is selected
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateSelectedItem(int item);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculate the size and viewport size of the scrollbars
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateScrollbars();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculate the maximum value for the vertical scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateVerticalScrollbarMaximum();

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Recalculate the maximum value for the horizontal scrollbar
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void updateHorizontalScrollbarMaximum();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draw the header text for a single column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void drawHeaderText(sf::RenderTarget& target, sf::RenderStates states, float columnWidth, float headerHeight, std::size_t column) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Draw the texts in a single column
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void drawColumn(sf::RenderTarget& target, sf::RenderStates states, std::size_t firstItem, std::size_t lastItem, std::size_t column, float columnWidth) const;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // This function is called every frame with the time passed since the last frame.
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        void update(sf::Time elapsedTime) override;


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Makes a copy of the widget
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        Widget::Ptr clone() const override
        {
            return std::make_shared<ListView>(*this);
        }


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    public:

        SignalInt onItemSelect  = {"ItemSelected"};   ///< An item was selected in the list view. Optional parameter: selected item index (-1 when deselecting)
        SignalInt onDoubleClick = {"DoubleClicked"};  ///< An item was double clicked. Optional parameter: selected item index


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        std::vector<Column> m_columns;
        std::vector<Item>   m_items;

        int m_selectedItem = -1;
        int m_hoveredItem = -1;

        float m_requestedHeaderHeight = 0;
        unsigned int m_itemHeight = 0;
        unsigned int m_requestedTextSize = 0;
        unsigned int m_textSize = 0;
        unsigned int m_headerTextSize = 0;
        unsigned int m_separatorWidth = 1;
        bool m_headerVisible = true;

        CopiedSharedPtr<ScrollbarChildWidget> m_horizontalScrollbar;
        CopiedSharedPtr<ScrollbarChildWidget> m_verticalScrollbar;
        Scrollbar::Policy m_verticalScrollbarPolicy = Scrollbar::Policy::Automatic;
        Scrollbar::Policy m_horizontalScrollbarPolicy = Scrollbar::Policy::Automatic;

        bool m_possibleDoubleClick = false; // Will be set to true after the first click, but gets reset to false when the second click does not occur soon after
        bool m_autoScroll = true; // Should the list view scroll to the bottom when a new item is added?

        // Cached renderer properties
        Borders   m_bordersCached;
        Borders   m_paddingCached;
        Color     m_borderColorCached;
        Color     m_separatorColorCached;
        Color     m_headerTextColorCached;
        Color     m_headerBackgroundColorCached;
        Color     m_backgroundColorCached;
        Color     m_backgroundColorHoverCached;
        Color     m_selectedBackgroundColorCached;
        Color     m_selectedBackgroundColorHoverCached;
        Color     m_textColorCached;
        Color     m_textColorHoverCached;
        Color     m_selectedTextColorCached;
        Color     m_selectedTextColorHoverCached;

        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_LIST_VIEW_HPP
