# MIT License

# Copyright (c) 2021 Solindek Developer

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

require 'rbconfig'

$os = "Other"

def os()
    @os ||= (
        host_os = RbConfig::CONFIG['host_os']
        case host_os
        when /mswin|msys|mingw|cygwin|bccwin|wince|emc/
            $os = "Win"
        when /darwin|mac os/
            $os = "MacOS"
        when /linux/
            $os = "Linux"
        when /solaris|bsd/
            $os = "Unix"
        else
            $os = "Other"
        end
    )
end

os()

$files = ""

Dir.glob(File.join("src/", '**', '*.cc')).select{|file| File.file?(file)}.each do |file|
    $files += file + " "
end

if $os == "Win"
    puts " >> g++ -o app.exe #{$files} -I./include/"
    system "g++ -o app.exe #{$files} -I./include/"
    if ARGV.length > 1
        system ARGV.join(" ")
    else
        system ".\\app.exe"
    end
else
    system "g++ -o app #{$files} -I./include/"
    if ARGV.length > 1
        system ARGV.join(" ")
    else
        system "./app.exe"
    end
end