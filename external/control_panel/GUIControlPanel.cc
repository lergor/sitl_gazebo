#include <sstream>
#include <gazebo/msgs/msgs.hh>
#include "GUIControlPanel.hh"

namespace {

    std::string situation_to_string(int situation) {
        switch (situation) {
            case NONE_BROKEN:
                return "NO BROKEN ROTORS";
            case ONE_BROKEN:
                return "ONE BROKEN ROTOR";
            case TWO_BROKEN:
                return "TWO BROKEN ROTORS";
            case THREE_BROKEN:
                return "THREE BROKEN ROTORS";
            default:
                return "UNKNOWN";
        }
    }
}


using namespace gazebo;

GZ_REGISTER_GUI_PLUGIN(GUIControlPanel)

GUIControlPanel::GUIControlPanel()
  : GUIPlugin()
{
    this->setStyleSheet(
            "QFrame { background-color : rgba(100, 100, 100, 255); color : white; }");
    main_layout_ = new QHBoxLayout();
    main_frame_ = new QFrame();
    frame_layout_ = new QVBoxLayout();

    //////////////////////// combo box ////////////////////////

    parameters_layout_ = new QHBoxLayout();

    construct_combo_box();
    parameters_layout_->addWidget(combo_box);

    frame_layout_->addLayout(parameters_layout_);

    //////////////////////// buttons ////////////////////////

    buttons_layout_ = new QHBoxLayout();

    go_button_ = new QPushButton(tr("GO"));
    go_button_->resize(20, 50);
    connect(go_button_, SIGNAL(clicked()), this, SLOT(on_stop_button()));

    buttons_layout_->addWidget(go_button_);

    frame_layout_->addLayout(buttons_layout_);

    //////////////////////// parameters ////////////////////////

    main_frame_->setLayout(frame_layout_);
    main_layout_->addWidget(main_frame_);
    frame_layout_->setContentsMargins(0, 0, 0, 0);
    main_layout_->setContentsMargins(0, 0, 0, 0);

    this->setLayout(main_layout_);

    this->move(10, 10);
    this->resize(200, 70);

    this->node = transport::NodePtr(new transport::Node());
    this->node->Init();

    this->control_panel_pub_ = this->node->Advertise<control_panel_msgs::msgs::ControlPanelMessage>("~/control_panel");
}

void GUIControlPanel::construct_combo_box() {
    combo_box = new QComboBox();
    combo_box->addItem("4/4 running");
    combo_box->addItem("3/4 running");
    combo_box->addItem("2/4 running");
    combo_box->addItem("1/4 running");
    combo_box->setCurrentIndex(2);
    combo_box->resize(120, 40);
}

void GUIControlPanel::publish_msg(int situation) {
    control_panel_msgs::msgs::ControlPanelMessage msg;
    msg.set_situation(situation);
    gzmsg << "[control panel] " << situation_to_string(situation) << std::endl;
    this->control_panel_pub_->Publish(msg);
}

void GUIControlPanel::on_stop_button() {
    publish_msg(combo_box->currentIndex());
}

