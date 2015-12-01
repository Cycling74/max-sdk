#!/usr/bin/env ruby -wKU
# encoding: utf-8

# Build all Max SDK examples
# Run from Terminal.app (Mac) or a MinGW prompt (Windows) 
# by cd'ing into the examples directory, and then running:
#   ruby build.rb
#
# On Windows you will need to have installed Ruby (1.9.3 recommended) from http://rubyinstaller.org/

sdk_examples_dir = "."
Dir.chdir sdk_examples_dir
sdk_examples_dir = Dir.pwd


# determine what platform we are on

$mac = (Object::RUBY_PLATFORM =~ /darwin/i) ? true : false
$win = !$mac

if $win
  # if we are on windows, figure out if we assume VisualStudio 2013
  $msbuild = "C:\\Program Files (x86)\\MSBuild\\12.0\\Bin\\MSBuild.exe"
end


# method to recursively build the projects

def build_projects_for_dir(path)
  puts
  puts "Building Projects for Directory: #{path}"
  
  Dir.foreach path do |filename|

    if $mac && filename.match(/.*\.xcodeproj/)
      puts "  Building #{filename}" 
      result = `cd "#{path}"; xcodebuild -project #{filename} 2>&1`
      if result.match(/\*\* BUILD SUCCEEDED \*\*/)
        puts "    (success)"
      else
        puts "    (FAIL) ************************************"
        #puts result
      end

    elsif $win && filename.match(/.*\.vcxproj/) && !filename.match(/.*\.vcxproj\..*/)
      puts "  Building #{filename} for Win32"
      result = `"#{$msbuild}" /target:rebuild /p:Platform=Win32 #{path}/#{filename} 2>&1`
      if result.match(/(0 error|up\-to\-date|Build succeeded\.)/)
        puts "    (success)"
      else
        puts "    (FAIL) ************************************"
        #puts result
      end

      puts "  Building #{filename} for x64"
      result = `"#{$msbuild}" /target:rebuild /p:Platform=x64 #{path}/#{filename} 2>&1`
      if result.match(/(0 error|up\-to\-date|Build succeeded\.)/)
        puts "    (success)"
      else
        puts "    (FAIL) ************************************"
        #puts result
      end

    elsif File.directory?("#{path}/#{filename}") && filename != "." && filename != ".." && filename != "build" && filename != "sysbuild" && filename != "c74support" && !filename.match(/.*\.xcodeproj/)
      build_projects_for_dir("#{path}/#{filename}")
    end
  end
  
  puts
end


build_projects_for_dir(sdk_examples_dir)


puts "You now have a Max Package that you can use."
puts "For more information on how to use a Max Package, see the Appendix on Distribution in the SDK documentation"
puts

