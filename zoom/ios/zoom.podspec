#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html.
# Run `pod lib lint zoom.podspec` to validate before publishing.
#
Pod::Spec.new do |s|
  s.name             = 'zoom'
  s.version          = '3.0.0'
  s.summary          = 'A new flutter plugin project.'
  s.description      = <<-DESC
A new flutter plugin project.
                       DESC
  s.homepage         = 'http://example.com'
  s.license          = { :file => '../LICENSE' }
  s.author           = { 'Your Company' => 'email@example.com' }
  s.source           = { :path => '.' }
  s.source_files = 'Classes/**/*'
  s.dependency 'Flutter'
  # MobileRTC 7.0.5 MinimumOSVersion is 15.0 (matches the app Podfile / Flutter 3.47 template).
  s.platform = :ios, '15.0'

  # The vendored xcframeworks only ship arm64 + arm64-simulator slices.
  s.pod_target_xcconfig = { 'OTHER_LDFLAGS' => '-framework MobileRTC -framework zoomcml', 'DEFINES_MODULE' => 'YES', 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'i386 x86_64' }
  s.swift_version = '5.0' 
  
  s.preserve_paths = 'MobileRTC.xcframework', 'zoomcml.xcframework', 'MobileRTCResources.bundle'
  s.vendored_frameworks = 'MobileRTC.xcframework', 'zoomcml.xcframework'
  s.resource = 'MobileRTCResources.bundle'
end
