#ifndef LAUNCHER_HPP_
#define LAUNCHER_HPP_

#include <string>

namespace
{
const std::string& launcherDialogXML = R"END(
    <?xml version="1.0" encoding="UTF-8"?>
    <!-- Generated with glade 3.20.4 -->
    <interface>
    <requires lib="gtk+" version="3.20"/>
    <object class="GtkDialog" id="reportDialog">
        <property name="can_focus">False</property>
        <property name="type_hint">dialog</property>
        <child internal-child="vbox">
        <object class="GtkBox">
            <property name="can_focus">False</property>
            <property name="orientation">vertical</property>
            <property name="spacing">2</property>
            <child internal-child="action_area">
            <object class="GtkButtonBox">
                <property name="can_focus">False</property>
                <property name="layout_style">end</property>
                <child>
                    <placeholder/>
                </child>
                <child>
                    <placeholder/>
                </child>
            </object>
            <packing>
                <property name="expand">False</property>
                <property name="fill">False</property>
                <property name="position">0</property>
            </packing>
            </child>
            <child>
            <object class="GtkBox">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="hexpand">True</property>
                <property name="vexpand">True</property>
                <child>
                <object class="GtkImage" id="reportImage">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="halign">start</property>
                    <property name="valign">start</property>
                    <property name="margin_left">10</property>
                    <property name="margin_right">10</property>
                    <property name="margin_top">10</property>
                    <property name="margin_bottom">10</property>
                </object>
                <packing>
                    <property name="expand">False</property>
                    <property name="fill">True</property>
                    <property name="position">0</property>
                </packing>
                </child>
                <child>
                <object class="GtkBox">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="orientation">vertical</property>
                    <child>
                    <object class="GtkLabel">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="halign">start</property>
                        <property name="margin_bottom">10</property>
                        <property name="label" translatable="yes">&lt;b&gt;Squally crashed out of the Vapor Web and his head exploded&lt;/b&gt;</property>
                        <property name="use_markup">True</property>
                        <property name="wrap">True</property>
                    </object>
                    <packing>
                        <property name="expand">False</property>
                        <property name="fill">True</property>
                        <property name="position">0</property>
                    </packing>
                    </child>
                    <child>
                    <object class="GtkLabel">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="halign">start</property>
                        <property name="margin_bottom">10</property>
                        <property name="label" translatable="yes">Mr Muskrat will be cleaning the walls for weeks, can you send us a bug report so we can "keep this from happening again?"</property>
                        <property name="use_markup">True</property>
                        <property name="wrap">True</property>
                    </object>
                    <packing>
                        <property name="expand">False</property>
                        <property name="fill">True</property>
                        <property name="position">1</property>
                    </packing>
                    </child>
                    <child>
                    <object class="GtkTextView" id="reportText">
                        <property name="visible">True</property>
                        <property name="can_focus">True</property>
                        <property name="margin_bottom">10</property>
                        <property name="vexpand">True</property>
                        <property name="wrap_mode">word</property>
                    </object>
                    <packing>
                        <property name="expand">False</property>
                        <property name="fill">True</property>
                        <property name="position">2</property>
                    </packing>
                    </child>
                </object>
                <packing>
                    <property name="expand">False</property>
                    <property name="fill">True</property>
                    <property name="position">1</property>
                </packing>
                </child>
            </object>
            <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">1</property>
            </packing>
            </child>
        </object>
        </child>
        <child>
        <placeholder/>
        </child>
    </object>
    </interface>
)END";
}
#endif
