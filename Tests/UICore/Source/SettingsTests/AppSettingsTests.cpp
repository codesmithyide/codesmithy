/*
    Copyright (c) 2016 Xavier Leclercq

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

void AddAppSettingsTests(TestSequence& testSequence)
{
    TestSequence* settingsTestSequence = new TestSequence("AppSettings tests", testSequence);

    new FileComparisonTest("Creation test 1", AppSettingsCreationTest1, *settingsTestSequence);
    new FileComparisonTest("Creation test 2", AppSettingsCreationTest2, *settingsTestSequence);
    new HeapAllocationErrorsTest("Creation test 3", AppSettingsCreationTest3, *settingsTestSequence);
    new HeapAllocationErrorsTest("Creation test 4", AppSettingsCreationTest4, *settingsTestSequence);
    new HeapAllocationErrorsTest("Creation test 5", AppSettingsCreationTest5, *settingsTestSequence);

    new FileComparisonTest("save test 1", AppSettingsSaveTest1, *settingsTestSequence);
    new FileComparisonTest("save test 2", AppSettingsSaveTest2, *settingsTestSequence);
    new FileComparisonTest("save test 3", AppSettingsSaveTest3, *settingsTestSequence);

    new HeapAllocationErrorsTest("createFileTypesFilter test 1", AppSettingsCreateFileTypesFilterTest1, *settingsTestSequence);
    new HeapAllocationErrorsTest("createFileTypesFilter test 2", AppSettingsCreateFileTypesFilterTest2, *settingsTestSequence);
    new HeapAllocationErrorsTest("createFileTypesFilter test 3", AppSettingsCreateFileTypesFilterTest3, *settingsTestSequence);
}

TestResult::EOutcome AppSettingsCreationTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "SettingsTests/AppSettingsCreationTest1.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "SettingsTests/AppSettingsCreationTest1.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, outputPath);
    result = TestResult::ePassed;

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}

TestResult::EOutcome AppSettingsCreationTest2(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "SettingsTests/AppSettingsCreationTest2.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "SettingsTests/AppSettingsCreationTest2.xml");

    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, outputPath);
    result = TestResult::ePassed;

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}

TestResult::EOutcome AppSettingsCreationTest3(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "SettingsTests/AppSettingsCreationTest3.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, inputPath);
    if ((appSettings.fileTypeAssociations().size() == 0) &&
        (appSettings.editorSettings().defaultSettings().fontSettings().faceName() == "Courier New") &&
        (appSettings.editorSettings().defaultSettings().fontSettings().pointSize() == 10))
    {
        result = TestResult::ePassed;
    }

    return result;
}

TestResult::EOutcome AppSettingsCreationTest4(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "SettingsTests/AppSettingsCreationTest4.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, inputPath);
    if (appSettings.fileTypeAssociations().size() == 1)
    {
        const CodeSmithy::FileTypeAssociation& association = *appSettings.fileTypeAssociations()[0];
        if ((association.documentTypeName() == "Bakefile") &&
            (association.association() == CodeSmithy::FileTypeAssociation::eDisabled) &&
            (association.actionType() == CodeSmithy::FileTypeAssociation::eAskAtStartup) &&
            (association.associatedProjectTypeName() == ""))
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}

TestResult::EOutcome AppSettingsCreationTest5(Test& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path inputPath(test.environment().getTestDataDirectory() / "SettingsTests/AppSettingsCreationTest5.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, inputPath);
    if (appSettings.fileTypeAssociations().size() == 1)
    {
        const CodeSmithy::FileTypeAssociation& association = *appSettings.fileTypeAssociations()[0];
        if ((association.documentTypeName() == "Bakefile") &&
            (association.association() == CodeSmithy::FileTypeAssociation::eOpen) &&
            (association.actionType() == CodeSmithy::FileTypeAssociation::eProjectType) &&
            (association.associatedProjectTypeName() == "CodeSmithy.Bakefile"))
        {
            result = TestResult::ePassed;
        }
    }

    return result;
}

TestResult::EOutcome AppSettingsSaveTest1(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

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

    result = TestResult::ePassed;

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}

TestResult::EOutcome AppSettingsSaveTest2(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "SettingsTests/AppSettingsSaveTest2.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "SettingsTests/AppSettingsSaveTest2.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, outputPath);

    appSettings.editorSettings().defaultSettings().fontSettings().setFaceName("Arial");
    appSettings.editorSettings().defaultSettings().fontSettings().setPointSize(12);
    appSettings.save();

    result = TestResult::ePassed;

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}

TestResult::EOutcome AppSettingsSaveTest3(FileComparisonTest& test)
{
    TestResult::EOutcome result = TestResult::eFailed;

    boost::filesystem::path outputPath(test.environment().getTestOutputDirectory() / "SettingsTests/AppSettingsSaveTest3.xml");
    boost::filesystem::remove(outputPath);
    boost::filesystem::path referencePath(test.environment().getReferenceDataDirectory() / "SettingsTests/AppSettingsSaveTest3.xml");

    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes, outputPath);

    appSettings.editorSettings().cppSettings().setUseDefaultFontSettings(false);
    appSettings.editorSettings().cppSettings().fontSettings().setFaceName("Arial");
    appSettings.editorSettings().cppSettings().fontSettings().setPointSize(12);
    appSettings.save();

    result = TestResult::ePassed;

    test.setOutputFilePath(outputPath);
    test.setReferenceFilePath(referencePath);

    return result;
}

TestResult::EOutcome AppSettingsCreateFileTypesFilterTest1()
{
    CodeSmithy::DocumentTypes documentTypes;
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes);
    if (appSettings.createFileTypesFilter() == "All Files (*.*)|*.*")
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome AppSettingsCreateFileTypesFilterTest2()
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes);
    if (appSettings.createFileTypesFilter() == "Bakefile (*.bkl)|*.bkl|All Files (*.*)|*.*")
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}

TestResult::EOutcome AppSettingsCreateFileTypesFilterTest3()
{
    CodeSmithy::DocumentTypes documentTypes;
    documentTypes.add(std::make_shared<CodeSmithy::BakefileType>());
    documentTypes.add(std::make_shared<CodeSmithy::CppFileType>());
    CodeSmithy::ProjectTypes projectTypes;
    CodeSmithy::AppSettings appSettings(documentTypes, projectTypes);
    if (appSettings.createFileTypesFilter() == "Bakefile (*.bkl)|*.bkl|C++ Source File (*.cpp;*.cxx)|*.cpp;*.cxx|All Files (*.*)|*.*")
    {
        return TestResult::ePassed;
    }
    else
    {
        return TestResult::eFailed;
    }
}
