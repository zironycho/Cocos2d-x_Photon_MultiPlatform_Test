//
//  CCRecursiveAction.cpp
//  Abstroku
//
//  Created by George Guy on 9/15/12.
//
//

#include "CCRecursiveAction.h"

USING_NS_CC;
//USING_NS_CC_EXT;

void CCRecursiveAction::runInstantInnerActionOnChildren( CCNode* target )
{
	CCAction* inner = this->getInnerAction();
	CCObject* o;
	CCNode* child;
	CCARRAY_FOREACH( target->getChildren(), o )
	{
		child = (CCNode*) o;
	    if( child != this->getExemptNode() )
	    {
			inner->startWithTarget( child );
			inner->update( 0 );
			inner->stop();
			this->runInstantInnerActionOnChildren( child );
	    }
	}
}

void CCRecursiveAction::update( float delta )
{
	CCAction* inner = this->getInnerAction();
    CCNode* target = this->getTarget();
    if( target == this->getExemptNode() ) return;
    
    if( this->getInnerIsInstant() )
    {
		inner->startWithTarget( target );
		inner->update( 0 );
		inner->stop();
		this->runInstantInnerActionOnChildren( target );
    }
    else
    {
		CCObject* o;
		CCNode* child;
		CCARRAY_FOREACH( target->getChildren(), o )
		{
			child = (CCNode*) o;
			child->runAction( (CCAction*) this->copy() );
		}

		target->runAction( inner );
    }
}

bool CCRecursiveAction::init( CCAction* innerAction, CCNode* exemptNode, int instant )
{
    CCAssert( innerAction, "CCRecursiveAction::init() -- innerAction must not be NULL" );
    this->setInnerAction( innerAction );
    if( instant < 0 ) this->setInnerIsInstant( (bool) dynamic_cast<CCActionInstant*>( innerAction ) );
    else this->setInnerIsInstant( instant );
    this->setExemptNode( exemptNode );
    return true;
}

CCRecursiveAction* CCRecursiveAction::create( CCAction* innerAction, CCNode* exemptNode )
{
    CCRecursiveAction* pRet = new CCRecursiveAction();
    
    if (pRet && pRet->init( innerAction, exemptNode ) )
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( pRet );
    }
    
    return pRet;
}

template<class targetType>
CaTTypedRecursiveAction<targetType>* CaTTypedRecursiveAction<targetType>::create( CCAction* innerAction, CCNode* exemptNode )
{
    CaTTypedRecursiveAction<targetType>* pRet = new CaTTypedRecursiveAction<targetType>();
    
    if (pRet && pRet->init( innerAction, exemptNode ) )
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( pRet );
    }
    
    return pRet;
}

template<class targetType>
void CaTTypedRecursiveAction<targetType>::update( float delta )
{
    CCNode* target = this->getTarget();
    if( target == this->getExemptNode() ) return;
    
    CCObject* o;
    CCNode* child;
    CCARRAY_FOREACH( target->getChildren(), o )
    {
        child = (CCNode*) o;
        child->runAction( (CCAction*) this->copy() );
    }
    
    if( dynamic_cast<targetType*>( target ) ) target->runAction( this->getInnerAction() );
}

/*template<class callFuncTargetType>
void CaTTypedRecursiveCallFunc<callFuncTargetType>::startWithTarget( CCNode* target )
{
    CCCallFunc* action = this->getInnerAction();
    action->setTargetCallback( this->getTarget() );
}

template<class callFuncTargetType>
CaTTypedRecursiveCallFunc<callFuncTargetType>* CaTTypedRecursiveCallFunc<callFuncTargetType>::create( CCCallFunc* innerAction, CCNode* exemptNode )
{
    CaTTypedRecursiveCallFunc<callFuncTargetType>* pRet = new CaTTypedRecursiveCallFunc<callFuncTargetType>();
    
    if (pRet && pRet->init( innerAction, exemptNode ) )
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_RELEASE_NULL( pRet );
    }
    
    return pRet;
}*/
