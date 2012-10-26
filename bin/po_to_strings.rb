#!/usr/bin/env ruby -wKU
#
# = .po to .strings converter
#
# Written by Eugene Pimenov <eugene@libc.st>.
#
# This file is distributed under the terms of the 2-clause BSD license.
# You can freely distribute/modify this source.
#
# This file is included in X-Chat Aqua project
#
# Posted by request from Jeong YunWon.
#
# Original document: https://gist.github.com/3958225

require "strscan"
require 'iconv'

class PoParser
  def initialize(po_file)
    @po_file = File.read(po_file)
  end
  
  def strings
    @strings||=parse
  end
  
  def save_strings(file)
    str = ""
    strings.each do |key,value|
     str += "/* nothing */\n#{key} = #{value};\n\n"
    end
    File.open(file, "w") do |f|
      f.write Iconv.iconv('utf-8', 'utf-8', str).first
    end
  end
private
  def parse
    out = []
    ss = StringScanner.new(@po_file)
    until ss.eos?
      case
      when ss.scan(/#/)
        ss.skip(/(.*)\n/)
      when ss.scan(/msgid /)
        if ss.scan(/""\n/)
          key = ""
          while ss.scan(/^"/)
            if a = ss.scan(/(.+?)"\n/)
              key += a[0..-3]
            end
          end
        else
          key = ss.scan(/"(.+?)"\n/)[1..-3]
        end
      when ss.scan(/msgstr /)
        if ss.scan(/""\n/)
          value = ""
          while ss.scan(/"/)
            if a=ss.scan(/(.+?)"\n/)
              value += a[0..-3]
            end
          end
        else
          value = a[1..-3] if a=ss.scan(/"(.+?)"\n/)
        end
        out<<["\"#{key}\"", "\"#{value}\""] if key
      when ss.scan(/\s+/)
      end
    end
    out
  end
end

Dir.glob("po/*.po") do |f|
  PoParser.new(f).save_strings(f.gsub(/\.po$/, '.strings'))
end
