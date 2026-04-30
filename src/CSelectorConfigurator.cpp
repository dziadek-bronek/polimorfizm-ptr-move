#include <cstdio>
#include <list>
#include <memory>
#include <vector>

#include "include/throw.hpp"

#include "CChildren/CChildren.hpp"
#include "include/CParent.hpp"

#include "include/child-creators.hpp"

#include "include/CSelector.hpp"
#include "include/CSimpleSelector.hpp"

#include "include/CSelectorConfiguratorIf.hpp"

#include "SoChildCreatorsProduction/createNewCSoChildCreatorsProducerChildCreator.hpp"

#include <dlfcn.h>

using UptrChCrIf = std::unique_ptr<CChildCreatorIf>;
using MapOfUptrChCrIf = std::list<UptrChCrIf>;

struct CChildCreatorExit : CChildCreatorIf
{
    CChildCreatorExit(int id_)
        : id(id_)
    {
        printf("ChildCreator constructor for  EXIT event %i \n", id);
    }
    virtual ~CChildCreatorExit()
    {
        printf("ChildCreator destructor for  EXIT event %i \n", id);
    }

    virtual void* createNewChildIfIsNumber(int id_)
    {
        if (id_ == id)
        {
            printf("CChildCreator on event %i : exit\n", id);
            THROW2("Clean exit", " (event 'EXIT' on input)");
        }
        return nullptr;
    }

  private:
    int id;
};

struct CConfigurator : CSelectorConfiguratorIf
{
    virtual ~CConfigurator() = default;

    virtual void init(void* initConfigVoidPtr)
    {
        initConfig = (std::vector<int>*)initConfigVoidPtr;
    }
    virtual void* initializeSelector()
    {
        // make this uniqu and resolve at the return
        selectorCoreMap = new MapOfUptrChCrIf;

        {
            /*
            SoChildCreatorsProducer is of class CChild, which creates Creators
            creating object defined by a certian .so files a creator which
            produces such a soChildCreatorsProducer is created and added to list
                this is for unification of access to soChildCreatorsProducer


                we use this creator x to generate y before pushing; pushing
            destroys x, thus we can not is soChildCreatorsProducer and we hold
            it for a while
                */




#define PACK_1(STRUCT_ID, OBJ_U_PTR_ID,		\
		F_A_TYPE, F_A, F_A_INIT		\
	     )					\
	    struct STRUCT_ID : VOID		\
	    {					\
		    F_A_TYPE F_A_ID;		\
	    };					\
	    std::unique_ptr<STRUCT_ID>		\
	    	OBJ_U_PTR_ID(new STRUCT_ID);	\
	    OBJ_U_PTR_ID->F_A_ID = F_A_INIT


            std::unique_ptr<CParent> soChildCreatorsProducer;

            {

	    PACK_1(X, x,
		MapOfUptrChCrIf*, selectorCoreMap, selectorCoreMap);

                UptrChCrIf creatorOfSoChildCreatorsProducer(
                    (CChildCreatorIf*)
                        createNewCSoChildCreatorsProducerChildCreator(
                            std::move(x)));

                soChildCreatorsProducer = std::unique_ptr<CParent>(
                    (CParent*)(creatorOfSoChildCreatorsProducer
                                   ->createNewChildIfIsNumber(221)));

                selectorCoreMap->push_back(
                    std::move(creatorOfSoChildCreatorsProducer));
                printf("initializeSelector: CChildCreator id=221, for "
                       "SoChildCreatorsProducer - "
                       "added to selector\n");
                fflush(NULL);
            }

	    PACK_1(X, x,
		MapOfUptrChCrIf*, selectorCoreMap, selectorCoreMap);
            struct Y
            {
                const char* fileName;
                const char* creatorName;
                const char* destroyerName;
                int id;
                std::unique_ptr<VOID> initParameterVoidUPtr;
            };
            Y adderSoChildData{
                "./libCConfigSoChild.so", "createNewCConfigSoChildExternC",
                "deleteCConfigSoChildExternC", 222, std::move(x)};


#if 0
#define PACK_5(STRUCT_ID, OBJ_PTR_ID		\
		F_A_TYPE, F_A, F_A_INIT,	\
		F_B_TYPE, F_B, F_B_INIT,	\
		F_C_TYPE, F_C, F_C_INIT,	\
		F_D_TYPE, F_D, F_D_INIT,	\
		F_E_TYPE, F_E, F_E_INIT,	\
		OBJ_PTR_ID			\
	     )					\
	    struct STRUCT_NAME : VOID		\
	    {					\
		    F_A_TYPE F_A;		\
		    F_B_TYPE F_B;		\
		    F_C_TYPE F_C;		\
		    F_D_TYPE F_D;		\
		    F_E_TYPE F_E;		\
	    };					\
	    std::unique_ptr<STRUCT_NAME>	\
	    	OBJ_U_PTR_ID = new STRUCT_NAME;	\
	    OBJ_NAME->F_A = F_A_INIT;		\
	    OBJ_NAME->F_B = F_B_INIT;		\
	    OBJ_NAME->F_C = F_C_INIT;		\
	    OBJ_NAME->F_D = F_D_INIT;		\
	    OBJ_NAME->F_E = F_E_INIT




	    PACK(X,
			    fileName, "./libCConfigSoChild.so"
			    creatorName, "createNewCConfigSoChildExternC"
			    destroyerName, "deleteCConfigSoChildExternC"
			    id, 222
			    UPtrVOID, initParameterVoidUPtr, std::move(x)
		)

#endif


            /*
            std::unique_ptr<Y> adderSoChildData(new Y);
                    adderSoChildData->fileName = "./libCConfigSoChild.so";
            adderSoChildData->creatorName = "createNewCConfigSoChildExternC";
            adderSoChildData->destroyerName = "deleteCConfigSoChildExternC";
            adderSoChildData->id = 222;
            adderSoChildData->initParameterVoidUPtr = std::move(x);
            */

            soChildCreatorsProducer->action(&adderSoChildData);

            printf("initializeSelector: CSoChildCreator id=222 for "
                   "CConfiSoChild - added to selector\n");
            fflush(NULL);
        }

        if (nullptr == initConfig)
        {
            return createNewCSelector(selectorCoreMap);
        }

        int vSize = initConfig->size();

        if (vSize <= 0)
        {
            selectorCoreMap->push_back(UptrChCrIf(new CChildCreatorExit(0)));
            return createNewCSelector(selectorCoreMap);
        }

        selectorCoreMap->push_back(
            UptrChCrIf(new CChildCreatorExit(initConfig->at(0))));

        for (int i = 1; i < vSize; ++i)
        {
            int creatorId = initConfig->at(i);
            if (creatorId < 0)
            {
                continue;
            }
            selectorCoreMap->push_back(UptrChCrIf(
                (CChildCreatorIf*)createChildCreatorWithId(i, creatorId)));
            printf(
                "CChildCreator, id=%i added to selector based on init config\n",
                creatorId);
            fflush(NULL);
        }

        return createNewCSelector(selectorCoreMap);
    }

  private:
    std::vector<int>* initConfig;
    MapOfUptrChCrIf* selectorCoreMap;
};

struct CSimpleConfigurator : CSelectorConfiguratorIf
{
    CSimpleConfigurator() {}

    virtual ~CSimpleConfigurator() = default;

    virtual void init(void*) {}

    virtual void* initializeSelector()
    {
        return createNewCSimpleSelector();
    }
};

void* createNewCSimpleSelectorConfigurator()
{
    return new CSimpleConfigurator;
}

void* createNewCSelectorConfigurator()
{

    return new CConfigurator;
}

extern "C" void* createNewCSimpleSelectorConfiguratorExternC()
{
    return new CSimpleConfigurator;
}

extern "C" void* createNewCSelectorConfiguratorExternC()
{
    return new CConfigurator();
}

extern "C" void deleteCSelectorConfiguratorExternC(void* configuratorPtr)
{
    delete (CSelectorConfiguratorIf*)configuratorPtr;
}
