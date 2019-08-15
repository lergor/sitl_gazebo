#pragma once
#include "gazebo/gazebo.hh"
#include <gazebo/common/Plugin.hh>
#include <gazebo/gui/GuiPlugin.hh>
#include <gazebo/transport/transport.hh>

#include "ControlPanelMessage.pb.h"

#define NONE_BROKEN     0
#define ONE_BROKEN      1
#define TWO_BROKEN      2
#define THREE_BROKEN    3

namespace gazebo
{
    class GAZEBO_VISIBLE GUIControlPanel : public GUIPlugin
{
    Q_OBJECT

    public:
    GUIControlPanel();

    virtual ~GUIControlPanel() = default;

    protected slots:
    void on_stop_button();

    private:

    transport::NodePtr node;
    transport::PublisherPtr control_panel_pub_;

    QFrame *main_frame_;
    QHBoxLayout *main_layout_;
    QVBoxLayout *frame_layout_;

    QHBoxLayout *buttons_layout_;
    QHBoxLayout *parameters_layout_;

    QPushButton *go_button_;
    QComboBox *combo_box;

    void construct_combo_box();

    void publish_msg(int situation);
};
}
