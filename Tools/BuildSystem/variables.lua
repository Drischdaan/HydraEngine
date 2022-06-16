output_directory = '%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}/'
build_directory = '%{wks.location}/build/bin/' .. output_directory .. '%{prj.name}'
int_build_directory = '%{wks.location}/build/bin-int/' .. output_directory .. '%{prj.name}'