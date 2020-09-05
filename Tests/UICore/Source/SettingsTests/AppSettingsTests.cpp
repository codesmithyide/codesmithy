/*
    Copyright (c) 2016-2019 Xavier Leclercq

    Permission is hereby granted, free of charge, to any person obtaining a
    copy of this software and associated documentation files (the "Software"),
    to deal in the Software without restriction, including without limitation
    the rights to use, copy, modify, merge, publish, distribute, sublicense,
    and/or sell copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
    THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/

#include "AppSettingsTests.h"
#include "CodeSmithy/UICore/Settings/AppSettings.h"
#include "CodeSmithy/Core/Documents/BakefileType.h"
#include "CodeSmithy/Core/Documents/CppFileType.h"
#include <boost/filesystem/operations.hpp>

using namespace Ishiko::Tests;

AppSettingsTests::AppSettingsTests(const TestNumber& number, const TestEnvironment& environment)
    : TestSequence(number, "AppSettings tests", environment)
{
    append<FileComparisonTest>("Construction test 1", ConstructionTest1);
    append<FileComparisonTest>("Construction test 2", ConstructionTest2);
    append<HeapAllocationErrorsTest>("Construction test 3", ConstructionTest3);
    append<HeapAllocationErrorsTest>("Construction test 4", ConstructionTest4);
    append<HeapAllocationErrorsTest>("Construction test 5", ConstructionTest5);
    append<HeapAllocationErrorsTest>("Construction test 6", ConstructionTest6);
    append<HeapAllocationErrorsTest>("Construction test 7", ConstructionTest7);
    append<FileComparisonTest>("save test 1", SaveTest1);
    append<FileComparisonTest>("save test 2", SaveTest2);
    append<FileComparisonTest>("save test 3", SaveTest3);
    append<HeapAllocationErrorsTest>("createFileTypesFilter test 1", CreateFileTypesFilterTest1);
    append<HeapAllocationErrorsTest>("createFileTypesFilter test 2", CreateFileTypesFilterTest2);
    append<HeapAllocationErrorsTest>("createFileTypesFilter test 3", CreateFileTypesFilterTest3);
}

void AppSettingsTests::ConstructionTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "AppSettingsTests_ConstructionTest1.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "AppSettingsTests_ConstructionTest1.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, outputPath);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void AppSettingsTests::ConstructionTest2(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "SettingsTests/AppSettingsCreationTest2.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "SettingsTests/AppSettingsCreationTest2.xml");

    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, outputPath);

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void AppSettingsTests::ConstructionTest3(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "SettingsTests/AppSettingsCreationTest3.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, inputPath);

    ISHTF_FAIL_IF_NEQ(appSettings.fileTypeAssociations().size(), 0);
    ISHTF_FAIL_IF_NEQ(appSettings.editorSettings().defaultSettings().fontSettings().faceName(), "Courier New");
    ISHTF_FAIL_IF_NEQ(appSettings.editorSettings().defaultSettings().fontSettings().pointSize(), 10);
    ISHTF_PASS();
}

void AppSettingsTests::ConstructionTest4(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "SettingsTests/AppSettingsCreationTest4.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, inputPath);

    ISHTF_ABORT_IF_NEQ(appSettings.fileTypeAssociations().size(), 1);

    const CodeSmithy::FileTypeAssociation& association = *appSettings.fileTypeAssociations()[0];

    ISHTF_FAIL_IF_NEQ(association.documentTypeName(), "Bakefile");
    ISHTF_FAIL_IF_NEQ(association.association(), CodeSmithy::FileTypeAssociation::eDisabled);
    ISHTF_FAIL_IF_NEQ(association.actionType(), CodeSmithy::FileTypeAssociation::eAskAtStartup);
    ISHTF_FAIL_IF_NEQ(association.associatedProjectTypeName(), "");
    ISHTF_PASS();
}

void AppSettingsTests::ConstructionTest5(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "SettingsTests/AppSettingsCreationTest5.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, inputPath);

    ISHTF_ABORT_IF_NEQ(appSettings.fileTypeAssociations().size(), 1);

    const CodeSmithy::FileTypeAssociation& association = *appSettings.fileTypeAssociations()[0];

    ISHTF_FAIL_IF_NEQ(association.documentTypeName(), "Bakefile");
    ISHTF_FAIL_IF_NEQ(association.association(), CodeSmithy::FileTypeAssociation::eOpen);
    ISHTF_FAIL_IF_NEQ(association.actionType(), CodeSmithy::FileTypeAssociation::eProjectType);
    ISHTF_FAIL_IF_NEQ(association.associatedProjectTypeName(), "CodeSmithy.Bakefile");
    ISHTF_PASS();
}

void AppSettingsTests::ConstructionTest6(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "SettingsTests/AppSettingsCreationTest6.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, inputPath);

    ISHTF_FAIL_IF_NEQ(appSettings.fileTypeAssociations().size(), 0);
    ISHTF_FAIL_IF_NEQ(appSettings.editorSettings().defaultSettings().fontSettings().faceName(), "Arial");
    ISHTF_FAIL_IF_NEQ(appSettings.editorSettings().defaultSettings().fontSettings().pointSize(), 12);
    ISHTF_PASS();
}

void AppSettingsTests::ConstructionTest7(Test& test)
{
    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "SettingsTests/AppSettingsCreationTest7.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, inputPath);

    ISHTF_FAIL_IF_NEQ(appSettings.fileTypeAssociations().size(), 0);
    ISHTF_FAIL_IF_NEQ(appSettings.editorSettings().defaultSettings().fontSettings().faceName(), "Courier New");
    ISHTF_FAIL_IF_NEQ(appSettings.editorSettings().defaultSettings().fontSettings().pointSize(), 10);
    ISHTF_FAIL_IF_NEQ(appSettings.editorSettings().cppSettings().overrideTheme(), true);
    ISHTF_FAIL_IF_NEQ(appSettings.editorSettings().cppSettings().fontSettings().faceName(), "Arial");
    ISHTF_FAIL_IF_NEQ(appSettings.editorSettings().cppSettings().fontSettings().pointSize(), 12);
    ISHTF_PASS();
}

void AppSettingsTests::SaveTest1(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "SettingsTests/AppSettingsSaveTest1.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "SettingsTests/AppSettingsSaveTest1.xml");

    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, outputPath);

    appSettings.fileTypeAssociations()[0]->setAssociation(CodeSmithy::FileTypeAssociation::eOpen);
    appSettings.fileTypeAssociations()[0]->setAction(CodeSmithy::FileTypeAssociation::eProjectType, "CodeSmithy.Bakefile");
    appSettings.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void AppSettingsTests::SaveTest2(FileComparisonTest& test)
{
   boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "SettingsTests/AppSettingsSaveTest2.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "SettingsTests/AppSettingsSaveTest2.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, outputPath);

    appSettings.editorSettings().defaultSettings().fontSettings().setFaceName("Arial");
    appSettings.editorSettings().defaultSettings().fontSettings().setPointSize(12);
    appSettings.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void AppSettingsTests::SaveTest3(FileComparisonTest& test)
{
    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "SettingsTests/AppSettingsSaveTest3.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "SettingsTests/AppSettingsSaveTest3.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, outputPath);

    appSettings.editorSettings().cppSettings().setOverrideTheme(true);
    appSettings.editorSettings().cppSettings().fontSettings().setFaceName("Arial");
    appSettings.editorSettings().cppSettings().fontSettings().setPointSize(12);
    appSettings.save();

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    ISHTF_PASS();
}

void AppSettingsTests::CreateFileTypesFilterTest1(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes);

    ISHTF_FAIL_IF_NEQ(appSettings.createFileTypesFilter(), "All Files (*.*)|*.*");
    ISHTF_PASS();
}

void AppSettingsTests::CreateFileTypesFilterTest2(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes);

    ISHTF_FAIL_IF_NEQ(appSettings.createFileTypesFilter(), "Bakefile (*.bkl)|*.bkl|All Files (*.*)|*.*");
    ISHTF_PASS();
}

void AppSettingsTests::CreateFileTypesFilterTest3(Test& test)
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());
    documentTypes.add(std::make_shared<CodeSmithy::CppFileType>());
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes);

    ISHTF_FAIL_IF_NEQ(appSettings.createFileTypesFilter(),
        "Bakefile (*.bkl)|*.bkl|C++ Source File (*.cpp;*.cxx)|*.cpp;*.cxx|All Files (*.*)|*.*");
    ISHTF_PASS();
}
