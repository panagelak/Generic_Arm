# Import PCL module
import pcl
# Load Point Cloud file
cloud = pcl.load_XYZRGB("tabletop.pcd")

# STEP 1 : Voxel Grid filter

# Create a VoxelGrid filter object for our input point cloud
vox = cloud.make_voxel_grid_filter()
# Choose a voxel (also known as leaf) size
# Note: this (0.01) is a decent choice of leaf size   
LEAF_SIZE = 0.01  
# Set the voxel (or leaf) size  
vox.set_leaf_size(LEAF_SIZE, LEAF_SIZE, LEAF_SIZE)
# Call the filter function to obtain the resultant downsampled point cloud
cloud_filtered = vox.filter()
# Save the Downsampled Point Cloud
filename = 'voxel_downsampled.pcd'
pcl.save(cloud_filtered, filename)


# STEP 2 : PassThrough filter

# Create a PassThrough filter object.
passthrough = cloud_filtered.make_passthrough_filter()
# Assign axis and range to the passthrough filter object.
filter_axis = 'z'
passthrough.set_filter_field_name(filter_axis)
axis_min = 0.6
axis_max = 1.1
passthrough.set_filter_limits(axis_min, axis_max)
# Finally use the filter function to obtain the resultant point cloud. 
cloud_filtered = passthrough.filter()
# Save the Cropped Point Cloud
filename = 'pass_through_filtered.pcd'
pcl.save(cloud_filtered, filename)

# STEP 3 : RANSAC plane segmentation

# Create the segmentation object
seg = cloud_filtered.make_segmenter()
# Set the model you wish to fit 
seg.set_model_type(pcl.SACMODEL_PLANE)
seg.set_method_type(pcl.SAC_RANSAC)

# Max distance for a point to be considered fitting the model
# Experiment with different values for max_distance 
# for segmenting the table
max_distance = 0.01
seg.set_distance_threshold(max_distance)
# Call the segment function to obtain set of inlier indices and model coefficients
inliers, coefficients = seg.segment()

#STEP 4 Extract the indices for the table and objects into Point Clouds

# Extract inliers
extracted_inliers = cloud_filtered.extract(inliers, negative=False)
# Save pcd for table
filename = 'extracted_inliers_table.pcd'
pcl.save(extracted_inliers, filename)


# Extract outliers
extracted_outliers = cloud_filtered.extract(inliers, negative=True)
# Save pcd for tabletop objects
filename = 'extracted_outliers_objects.pcd'
pcl.save(extracted_outliers, filename)

'''
# STEP 5: Optional Outlier filter

# Much like the previous filters, we start by creating a filter object: 
outlier_filter = cloud_filtered.make_statistical_outlier_filter()

# Set the number of neighboring points to analyze for any given point
outlier_filter.set_mean_k(50)

# Set threshold scale factor
x = 1.0

# Any point with a mean distance larger than global (mean distance+x*std_dev) will be considered outlier
outlier_filter.set_std_dev_mul_thresh(x)

# Finally call the filter function for magic
cloud_filtered = outlier_filter.filter()
'''

