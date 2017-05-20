#pragma once

#include <memory>
#include <map>

#include <core/src/vector-def.hpp>

#include "applicationGraphicsDevice.hpp"

namespace sushi { namespace wnd {

    class window;
}}

namespace sushi { namespace app {

    class application;

    class applicationDelegate {

        friend class application;

    public:

        virtual void                                                receivedLowMemory       (application* const application) = 0;
    };

    /**
     *
     * Class that the implementing OS inherits from so that any sushi event can be piped back to the OS.
     *
     */
    class applicationDriver {

    public:

        // Delegate that needs to be set so that the OS can talk with sushi.
        std::weak_ptr<applicationDelegate>                          delegate;


        /**
         *
         * Method to implement when Sushi wants to create an application instance.
         *
         * @param application The application instance to initialize
         * @param data OS-specific data that helps with the initialization of the application.
         */
        SU_DEF_FUNC(ThreadSafe)
        virtual void                                                initialize              (application* const application, void* const data) const = 0;

        /**
         *
         * Method to implement when Sushi is about to destroy the application instance.
         *
         * @param application The application instance to destroy.
         */
        SU_DEF_FUNC(NotThreadSafe, SameThreadAsInitialization)
        virtual void                                                destroy                 (application* const application) const = 0;


        /**
         *
         * Method to implement when Sushi is about to start the application.
         *
         * @param application The application instance to start.
         */
        SU_DEF_FUNC(NotThreadSafe, SameThreadAsInitialization)
        virtual void                                                run                     (application* const application) const = 0;
    };

    class application final: applicationDelegate {

    protected:

        std::shared_ptr<applicationGraphicsDevice>                  device_graphics;
        std::shared_ptr<void>                                       device_sound;

        std::shared_ptr<void>                                       device_storage;

    private:

        std::unique_ptr<applicationDriver>                          driver;


        static application*                                         instance;

        application                                                                         ();

        ~application                                                                        ();


    public:

        static void                                                 initialize              (std::unique_ptr<applicationDriver>& driver, void* const data);

        static void                                                 destroy                 ();


        static void                                                 run                     ();


        static application* const                                   get_instance            ();


        inline const std::unique_ptr<applicationDriver>&            get_driver              () const { return driver; }


        inline const std::shared_ptr<applicationGraphicsDevice>&    get_device_graphics     () const { return device_graphics;  }

        inline const std::shared_ptr<void>&                         get_device_sound        () const { return device_sound;     }


        inline const std::shared_ptr<void>&                         get_device_storage      () const { return device_storage;   }


        void                                                        bindWindow              (const std::shared_ptr<wnd::window>& window);

        void                                                        unbindWindow            (const std::shared_ptr<wnd::window>& window);

    private:

        void                                                        receivedLowMemory       (application *const application) override;
    };
}}
