﻿namespace CETech
{
    /// <summary>
    ///     Render system
    /// </summary>
    public static partial class RenderSystem
    {
        /// <summary>
        ///     Render backend type.
        /// </summary>
        public enum BackendType
        {
            /// <summary>
            ///     No backend given.
            /// </summary>
            Null,

            /// <summary>
            ///     Direct3D 9
            /// </summary>
            Direct3D9,

            /// <summary>
            ///     Direct3D 11
            /// </summary>
            Direct3D11,

            /// <summary>
            ///     Direct3D 12
            /// </summary>
            Direct3D12,

            /// <summary>
            ///     Apple Metal.
            /// </summary>
            Metal,

            /// <summary>
            ///     OpenGL ES
            /// </summary>
            OpenGLES,

            /// <summary>
            ///     OpenGL
            /// </summary>
            OpenGL,

            /// <summary>
            ///     Vulkan
            /// </summary>
            Vulkan,

            /// <summary>
            ///     Used during initialization; specifies that the library should
            ///     pick the best renderer for the running hardware and OS.
            /// </summary>
            Default
        }

        /// <summary>
        ///     Init render system.
        /// </summary>
        /// <param name="window">Window for render context</param>
        /// <param name="type">Render backend</param>
        public static void Init(Window window, BackendType type)
        {
            InitImpl(window, type);
        }

		public static void Shutdown()
		{
			ShutdownImpl ();
		}

        public static void RenderWorld(int world, int camera)
        {
            RenderWorldImpl(world, camera);
        }


        /// <summary>
        ///     Resize render view
        /// </summary>
        /// <param name="width">New width</param>
        /// <param name="height">New height</param>
        public static void Resize(int width, int height)
        {
            ResizeImpl(width, height);
        }

        public static void SetDebug(bool enabled)
        {
            SetDebugImpl(enabled);
        }

        public static void SaveScreenShot(string filename)
        {
            SaveScreenShotImpl(filename);
        }

        public static void BeginCapture()
        {
            BeginCaptureImpl();
        }


        public static void EndCapture()
        {
            EndCaptureImpl();
        }
    }
}