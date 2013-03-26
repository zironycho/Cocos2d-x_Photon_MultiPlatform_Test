/****************************************************************************
 Copyright (c) 2013 George Guy

 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef TestCpp_CCRoomTableCell_h
#define TestCpp_CCRoomTableCell_h

#include "cocos-ext.h"
#include "CCNetworkLogic.h"

class CCRoomTableCell : public cocos2d::extension::CCTableViewCell
{
    CC_PROPERTY( bool, _hasRoom, HasRoom );
    CC_SYNTHESIZE( cocos2d::CCLabelTTF*, _label, Label );
    ExitGames::LoadBalancing::Room* _roomInfo;
    
public:
    CCRoomTableCell();
    ~CCRoomTableCell();
    
    virtual bool init();
    CREATE_FUNC( CCRoomTableCell );
    
    virtual bool init( ExitGames::LoadBalancing::Room& room );
    static CCRoomTableCell* create( ExitGames::LoadBalancing::Room& room );
    
    CC_PROPERTY(ExitGames::LoadBalancing::Room*, _room, Room );
};

#endif
