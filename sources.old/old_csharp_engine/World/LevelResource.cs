﻿using System.Collections.Generic;
using System.IO;
using System.Yaml;
using CETech.Develop;
using CETech.Resource;
using MsgPack.Serialization;

namespace CETech.World
{
    public class LevelResource
    {
        /// <summary>
        ///     ResourceManager type
        /// </summary>
        public static readonly long Type = StringId64.FromString("level");

        /// <summary>
        ///     ResourceManager loader
        /// </summary>
        /// <param name="input">ResourceManager data stream</param>
        /// <returns>ResourceManager data</returns>
        public static object ResourceLoader(Stream input)
        {
            return MessagePackSerializer.Get<CompiledResource>().Unpack(input);
        }

        /// <summary>
        ///     ResourceManager offline.
        /// </summary>
        /// <param name="data">Data</param>
        public static void ResourceOffline(object data)
        {
        }

        /// <summary>
        ///     ResourceManager online
        /// </summary>
        /// <param name="data">Data</param>
        public static void ResourceOnline(object data)
        {
        }

        /// <summary>
        ///     ResourceManager unloader
        /// </summary>
        /// <param name="data">data</param>
        public static void ResourceUnloader(object data)
        {
        }

#if CETECH_DEVELOP
        /// <summary>
        ///     ResourceManager compiler
        /// </summary>
        /// <param name="capi">Compiler api</param>
        public static void Compile(ResourceCompiler.CompilatorApi capi)
        {
            TextReader input = new StreamReader(capi.ResourceFile);
            var yaml = YamlNode.FromYaml(input);

            var rootNode = yaml[0] as YamlMapping;
            var unitsNode = rootNode["units"] as YamlMapping;

            var packer = new ConsoleServer.ResponsePacker();

            var units_names = new List<long>(unitsNode.Count);

            packer.PackMapHeader(2);
            packer.Pack("units");

            packer.PackArrayHeader(unitsNode.Count);


            foreach (var unit in unitsNode)
            {
                var unit_def = unit.Value as YamlMapping;
                var name = unit_def["name"] as YamlScalar;

                units_names.Add(StringId64.FromString(name.Value));

                UnitResource.Compile(unit_def, packer, capi);
            }

            packer.Pack("units_name");
            packer.PackArrayHeader(units_names.Count);
            for (var i = 0; i < units_names.Count; i++)
            {
                packer.Pack(units_names[i]);
            }

            packer.GetMemoryStream().WriteTo(capi.BuildFile);
        }
#endif

        public static object ResourceReloader(long name, object new_data)
        {
            return new_data;
        }

        public class CompiledResource
        {
            public UnitResource.CompiledResource[] units { get; set; }
            public long[] units_name { get; set; }
        }
    }
}