// Copyright (c) 2023, ETH Zurich and UNC Chapel Hill.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//
//     * Neither the name of ETH Zurich and UNC Chapel Hill nor the names of
//       its contributors may be used to endorse or promote products derived
//       from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Author: Johannes L. Schoenberger (jsch-at-demuc-dot-de)

#include "ui/reconstruction_options_widget.h"

#include "controllers/incremental_mapper.h"

namespace colmap {

MapperGeneralOptionsWidget::MapperGeneralOptionsWidget(QWidget* parent,
                                                       OptionManager* options)
    : OptionsWidget(parent) {
  AddOptionBool(&options->mapper->multiple_models, "multiple_models");
  AddOptionInt(&options->mapper->max_num_models, "max_num_models");
  AddOptionInt(&options->mapper->max_model_overlap, "max_model_overlap");
  AddOptionInt(&options->mapper->min_model_size, "min_model_size");
  AddOptionBool(&options->mapper->extract_colors, "extract_colors");
  AddOptionInt(&options->mapper->num_threads, "num_threads", -1);
  AddOptionInt(&options->mapper->min_num_matches, "min_num_matches");
  AddOptionBool(&options->mapper->ignore_watermarks, "ignore_watermarks");
  AddOptionDirPath(&options->mapper->snapshot_path, "snapshot_path");
  AddOptionInt(&options->mapper->snapshot_images_freq, "snapshot_images_freq",
               0);
}

MapperTriangulationOptionsWidget::MapperTriangulationOptionsWidget(
    QWidget* parent, OptionManager* options)
    : OptionsWidget(parent) {
  AddOptionInt(&options->mapper->triangulation.max_transitivity,
               "max_transitivity");
  AddOptionDouble(&options->mapper->triangulation.create_max_angle_error,
                  "create_max_angle_error [deg]");
  AddOptionDouble(&options->mapper->triangulation.continue_max_angle_error,
                  "continue_max_angle_error [deg]");
  AddOptionDouble(&options->mapper->triangulation.merge_max_reproj_error,
                  "merge_max_reproj_error [px]");
  AddOptionDouble(&options->mapper->triangulation.re_max_angle_error,
                  "re_max_angle_error [deg]");
  AddOptionDouble(&options->mapper->triangulation.re_min_ratio, "re_min_ratio");
  AddOptionInt(&options->mapper->triangulation.re_max_trials, "re_max_trials");
  AddOptionDouble(&options->mapper->triangulation.complete_max_reproj_error,
                  "complete_max_reproj_error [px]");
  AddOptionInt(&options->mapper->triangulation.complete_max_transitivity,
               "complete_max_transitivity");
  AddOptionDouble(&options->mapper->triangulation.min_angle, "min_angle [deg]",
                  0, 180);
  AddOptionBool(&options->mapper->triangulation.ignore_two_view_tracks,
                "ignore_two_view_tracks");
}

MapperRegistrationOptionsWidget::MapperRegistrationOptionsWidget(
    QWidget* parent, OptionManager* options)
    : OptionsWidget(parent) {
  AddOptionDouble(&options->mapper->mapper.abs_pose_max_error,
                  "abs_pose_max_error [px]");
  AddOptionInt(&options->mapper->mapper.abs_pose_min_num_inliers,
               "abs_pose_min_num_inliers");
  AddOptionDouble(&options->mapper->mapper.abs_pose_min_inlier_ratio,
                  "abs_pose_min_inlier_ratio");
  AddOptionInt(&options->mapper->mapper.max_reg_trials, "max_reg_trials", 1);
}

MapperInitializationOptionsWidget::MapperInitializationOptionsWidget(
    QWidget* parent, OptionManager* options)
    : OptionsWidget(parent) {
  AddOptionInt(&options->mapper->init_image_id1, "init_image_id1", -1);
  AddOptionInt(&options->mapper->init_image_id2, "init_image_id2", -1);
  AddOptionInt(&options->mapper->init_num_trials, "init_num_trials");
  AddOptionInt(&options->mapper->mapper.init_min_num_inliers,
               "init_min_num_inliers");
  AddOptionDouble(&options->mapper->mapper.init_max_error, "init_max_error");
  AddOptionDouble(&options->mapper->init_image_x, "init_image_x [m]");
  AddOptionDouble(&options->mapper->init_image_y, "init_image_y [m]");
  AddOptionDouble(&options->mapper->init_image_z, "init_image_z [m]");
  AddOptionDouble(&options->mapper->init_image_roll, "init_image_roll [deg]");
  AddOptionDouble(&options->mapper->init_image_pitch, "init_image_pitch [deg]");
  AddOptionDouble(&options->mapper->init_image_yaw, "init_image_yaw [deg]");
  AddOptionDouble(&options->mapper->mapper.init_max_forward_motion,
                  "init_max_forward_motion");
  AddOptionDouble(&options->mapper->mapper.init_min_tri_angle,
                  "init_min_tri_angle [deg]");
  AddOptionInt(&options->mapper->mapper.init_max_reg_trials,
               "init_max_reg_trials", 1);
}

MapperBundleAdjustmentOptionsWidget::MapperBundleAdjustmentOptionsWidget(
    QWidget* parent, OptionManager* options)
    : OptionsWidget(parent) {
  AddSection("Camera parameters");
  AddOptionBool(&options->mapper->ba_refine_focal_length,
                "refine_focal_length");
  AddOptionBool(&options->mapper->ba_refine_principal_point,
                "refine_principal_point");
  AddOptionBool(&options->mapper->ba_refine_extra_params,
                "refine_extra_params");

  AddSpacer();

  AddSection("Local Bundle Adjustment");
  AddOptionInt(&options->mapper->ba_local_num_images, "num_images");
  AddOptionInt(&options->mapper->ba_local_max_num_iterations,
               "max_num_iterations");
  AddOptionInt(&options->mapper->ba_local_max_refinements, "max_refinements",
               1);
  AddOptionDouble(&options->mapper->ba_local_max_refinement_change,
                  "max_refinement_change", 0, 1, 1e-6, 6);

  AddSpacer();

  AddSection("Global Bundle Adjustment");
  AddOptionBool(&options->mapper->ba_global_use_pba,
                "use_pba\n(requires SIMPLE_RADIAL)");
  AddOptionDouble(&options->mapper->ba_global_images_ratio, "images_ratio");
  AddOptionInt(&options->mapper->ba_global_images_freq, "images_freq");
  AddOptionDouble(&options->mapper->ba_global_points_ratio, "points_ratio");
  AddOptionInt(&options->mapper->ba_global_points_freq, "points_freq");
  AddOptionInt(&options->mapper->ba_global_max_num_iterations,
               "max_num_iterations");
  AddOptionInt(&options->mapper->ba_global_pba_gpu_index, "pba_gpu_index", -1);
  AddOptionInt(&options->mapper->ba_global_max_refinements, "max_refinements",
               1);
  AddOptionDouble(&options->mapper->ba_global_max_refinement_change,
                  "max_refinement_change", 0, 1, 1e-6, 6);
}

MapperFilteringOptionsWidget::MapperFilteringOptionsWidget(
    QWidget* parent, OptionManager* options)
    : OptionsWidget(parent) {
  AddOptionDouble(&options->mapper->min_focal_length_ratio,
                  "min_focal_length_ratio");
  AddOptionDouble(&options->mapper->max_focal_length_ratio,
                  "max_focal_length_ratio");
  AddOptionDouble(&options->mapper->max_extra_param, "max_extra_param");

  AddOptionDouble(&options->mapper->mapper.filter_max_reproj_error,
                  "filter_max_reproj_error [px]");
  AddOptionDouble(&options->mapper->mapper.filter_min_tri_angle,
                  "filter_min_tri_angle [deg]");
  AddOptionDouble(&options->mapper->mapper.proj_max_dist_error,
                  "depth_proj_max_dist_error [m]");
  AddOptionDouble(&options->mapper->mapper.icp_max_dist_error,
                  "icp_max_dist_error [m]");
}

MapperLidarConstraintingOptionsWidget::MapperLidarConstraintingOptionsWidget(QWidget* parent,
                                                                            OptionManager* options)
    : OptionsWidget(parent) {
      AddOptionInt(&options->mapper->first_image_fixed_frames,"first_image_fixed_frames");
      AddOptionBool(&options->mapper->if_add_lidar_constraint, "if_add_lidar_constraint");
      AddOptionFilePath(&options->mapper->lidar_pointcloud_path, "lidar_map_path");
      AddOptionBool(&options->mapper->if_import_pose_prior, "if_import_image_pose_prior"); 
      AddOptionFilePath(&options->mapper->image_pose_prior_path, "image_pose_prior_path");
      AddOptionDirPath(&options->mapper->image_pose_save_folder, "save_image_pose_folder");
      AddOptionBool(&options->mapper->if_add_lidar_corresponding, "if_add_lidar_correspondence");
      AddOptionBool(&options->mapper->if_add_lidar_display, "if_add_lidar_display");
      AddOptionDouble(&options->mapper->proj_lidar_constraint_weight, "depth_proj_constraint_weight");
      AddOptionDouble(&options->mapper->icp_lidar_constraint_weight, "icp_nonground_constraint_weight");
      AddOptionDouble(&options->mapper->icp_ground_lidar_constraint_weight, "icp_ground_constraint_weight");

      AddOptionInt(&options->mapper->min_proj_num,"depth_proj_association_num");
      AddOptionDouble(&options->mapper->depth_image_scale, "depth_image_scale");
      AddOptionDouble(&options->mapper->choose_meter,"max_depth_proj_dist");
      AddOptionInt(&options->mapper->min_proj_scale, "min_depth_inflation");
      AddOptionDouble(&options->mapper->min_proj_dist,"min_depth_proj_dist");
      AddOptionInt(&options->mapper->max_proj_scale, "max_depth_inflation");
      AddOptionDouble(&options->mapper->min_lidar_proj_dist,"min_lidar_proj_dist");
      AddOptionBool(&options->mapper->if_save_depth_image, "if_save_depth_image");
      AddOptionDirPath(&options->mapper->depth_image_folder, "save_depth_image_folder");
      AddOptionBool(&options->mapper->if_save_lidar_frame, "if_save_lidar_pcd");
      AddOptionDirPath(&options->mapper->lidar_frame_folder, "save_lidar_pcd_folder");
      AddOptionDouble(&options->mapper->submap_length,"submap_length");
      AddOptionDouble(&options->mapper->submap_width,"submap_width");
      AddOptionDouble(&options->mapper->submap_height,"submap_height");

      AddOptionDouble(&options->mapper->kdtree_max_search_range,"kdtree_max_search_dist");
      AddOptionDouble(&options->mapper->kdtree_min_search_range,"kdtree_min_search_dist");
      AddOptionDouble(&options->mapper->search_range_drop_speed,"kdtree_search_dist_drop");

      AddOptionDouble(&options->mapper->ba_spherical_search_radius,"ba_sphere_radius");
      AddOptionInt(&options->mapper->ba_match_features_threshold,"ba_min_matched_features");

    }
ReconstructionOptionsWidget::ReconstructionOptionsWidget(QWidget* parent,
                                                         OptionManager* options)
    : QWidget(parent) {
  setWindowFlags(Qt::Dialog);
  setWindowModality(Qt::ApplicationModal);
  setWindowTitle("Reconstruction options");

  QGridLayout* grid = new QGridLayout(this);

  QTabWidget* tab_widget = new QTabWidget(this);
  tab_widget->setElideMode(Qt::TextElideMode::ElideRight);
  tab_widget->addTab(new MapperGeneralOptionsWidget(this, options),
                     tr("General"));
  tab_widget->addTab(new MapperInitializationOptionsWidget(this, options),
                     tr("Init"));
  tab_widget->addTab(new MapperRegistrationOptionsWidget(this, options),
                     tr("Registration"));
  tab_widget->addTab(new MapperTriangulationOptionsWidget(this, options),
                     tr("Triangulation"));
  tab_widget->addTab(new MapperBundleAdjustmentOptionsWidget(this, options),
                     tr("Bundle"));
  tab_widget->addTab(new MapperFilteringOptionsWidget(this, options),
                     tr("Filter"));
  tab_widget->addTab(new MapperLidarConstraintingOptionsWidget(this, options),
                     tr("Lidar"));                   

  grid->addWidget(tab_widget, 0, 0);
}

}  // namespace colmap
